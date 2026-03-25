-- Normaliza campos ENUM para uma tabela de dominios/status.
-- Execute em um schema ja carregado com a estrutura atual (biopower.sql).
-- Se precisar fazer rollback, restaure o backup anterior (este script remove os ENUM).

START TRANSACTION;

-- 1) Tabela de dominios/status genericos.
CREATE TABLE IF NOT EXISTS status_diversos (
  sta_id INT NOT NULL AUTO_INCREMENT,
  sta_dominio VARCHAR(50) NOT NULL,
  sta_codigo VARCHAR(50) NOT NULL,
  sta_descricao VARCHAR(120) DEFAULT NULL,
  PRIMARY KEY (sta_id),
  UNIQUE KEY uq_status_dominio_codigo (sta_dominio, sta_codigo)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- 2) Popular dominios usados pelos antigos ENUMs.
INSERT IGNORE INTO status_diversos (sta_dominio, sta_codigo, sta_descricao) VALUES
  -- Agendamentos
  ('agendamento_status','CONFIRMADO','Agendamento confirmado'),
  ('agendamento_status','AGUARDANDO_PAGAMENTO','Aguardando pagamento'),
  ('agendamento_status','CANCELADO','Agendamento cancelado'),
  ('agendamento_status','CONCLUIDO','Agendamento concluido'),
  -- Devolucoes
  ('devolucao_status','PENDENTE','Aguardando avaliacao'),
  ('devolucao_status','APROVADO','Devolucao aprovada'),
  ('devolucao_status','RECUSADO','Devolucao recusada'),
  -- Fluxo de caixa (tipo)
  ('fluxo_caixa_tipo','RECEITA','Entrada de recursos'),
  ('fluxo_caixa_tipo','DESPESA','Saida de recursos'),
  -- Pedidos de compra
  ('pedido_status','SOLICITADO','Pedido solicitado'),
  ('pedido_status','EM_ANDAMENTO','Pedido em andamento'),
  ('pedido_status','CONCLUIDO','Pedido concluido'),
  -- Vendas - metodo de pagamento
  ('venda_metodo_pagamento','PIX','Pagamento via PIX'),
  ('venda_metodo_pagamento','CREDITO','Cartao de credito'),
  ('venda_metodo_pagamento','DEBITO','Cartao de debito'),
  ('venda_metodo_pagamento','BOLETO','Pagamento por boleto'),
  -- Vendas - status
  ('venda_status','AGUARDANDO','Aguardando pagamento'),
  ('venda_status','PAGO','Pagamento confirmado'),
  ('venda_status','CANCELADO','Venda cancelada');

-- Helpers para defaults
SET @sta_age_default := (SELECT sta_id FROM status_diversos WHERE sta_dominio='agendamento_status' AND sta_codigo='AGUARDANDO_PAGAMENTO');
SET @sta_dev_default := (SELECT sta_id FROM status_diversos WHERE sta_dominio='devolucao_status' AND sta_codigo='PENDENTE');
SET @sta_ped_default := (SELECT sta_id FROM status_diversos WHERE sta_dominio='pedido_status' AND sta_codigo='SOLICITADO');
SET @sta_ven_status_default := (SELECT sta_id FROM status_diversos WHERE sta_dominio='venda_status' AND sta_codigo='AGUARDANDO');
SET @sta_ven_metodo_default := (SELECT sta_id FROM status_diversos WHERE sta_dominio='venda_metodo_pagamento' AND sta_codigo='PIX');

-- 3) tb_Agendamentos: substituir age_status (ENUM) por referencia.
ALTER TABLE tb_Agendamentos ADD COLUMN age_status_id INT NULL AFTER age_data_hora;

UPDATE tb_Agendamentos a
  JOIN status_diversos s ON s.sta_dominio='agendamento_status' AND s.sta_codigo=a.age_status
  SET a.age_status_id = s.sta_id;

ALTER TABLE tb_Agendamentos DROP COLUMN age_status;

ALTER TABLE tb_Agendamentos
  MODIFY age_status_id INT NOT NULL DEFAULT @sta_age_default,
  ADD CONSTRAINT fk_age_status FOREIGN KEY (age_status_id) REFERENCES status_diversos(sta_id);

-- 4) tb_Devolucoes: substituir dev_status (ENUM).
ALTER TABLE tb_Devolucoes ADD COLUMN dev_status_id INT NULL AFTER dev_caminho_nota_fiscal;
UPDATE tb_Devolucoes d
  JOIN status_diversos s ON s.sta_dominio='devolucao_status' AND s.sta_codigo=d.dev_status
  SET d.dev_status_id = s.sta_id;
ALTER TABLE tb_Devolucoes DROP COLUMN dev_status;
ALTER TABLE tb_Devolucoes
  MODIFY dev_status_id INT NOT NULL DEFAULT @sta_dev_default,
  ADD CONSTRAINT fk_dev_status FOREIGN KEY (dev_status_id) REFERENCES status_diversos(sta_id);

-- 5) tb_Fluxo_Caixa: substituir flu_tipo (ENUM).
ALTER TABLE tb_Fluxo_Caixa ADD COLUMN flu_tipo_id INT NULL AFTER flu_id;
UPDATE tb_Fluxo_Caixa f
  JOIN status_diversos s ON s.sta_dominio='fluxo_caixa_tipo' AND s.sta_codigo=f.flu_tipo
  SET f.flu_tipo_id = s.sta_id;
ALTER TABLE tb_Fluxo_Caixa DROP COLUMN flu_tipo;
ALTER TABLE tb_Fluxo_Caixa
  MODIFY flu_tipo_id INT NOT NULL,
  ADD CONSTRAINT fk_flu_tipo FOREIGN KEY (flu_tipo_id) REFERENCES status_diversos(sta_id);

-- 6) tb_Pedidos_Compra: substituir ped_status (ENUM).
ALTER TABLE tb_Pedidos_Compra ADD COLUMN ped_status_id INT NULL AFTER ped_prazo_entrega_previsto;
UPDATE tb_Pedidos_Compra p
  JOIN status_diversos s ON s.sta_dominio='pedido_status' AND s.sta_codigo=p.ped_status
  SET p.ped_status_id = s.sta_id;
ALTER TABLE tb_Pedidos_Compra DROP COLUMN ped_status;
ALTER TABLE tb_Pedidos_Compra
  MODIFY ped_status_id INT NOT NULL DEFAULT @sta_ped_default,
  ADD CONSTRAINT fk_ped_status FOREIGN KEY (ped_status_id) REFERENCES status_diversos(sta_id);

-- 7) tb_Vendas: substituir ven_metodo_pagamento (ENUM) e ven_status_venda (ENUM).
ALTER TABLE tb_Vendas
  ADD COLUMN ven_metodo_pagamento_id INT NULL AFTER ven_valor_total,
  ADD COLUMN ven_status_id INT NULL AFTER ven_metodo_pagamento_id;

UPDATE tb_Vendas v
  LEFT JOIN status_diversos sm ON sm.sta_dominio='venda_metodo_pagamento' AND sm.sta_codigo=v.ven_metodo_pagamento
  LEFT JOIN status_diversos ss ON ss.sta_dominio='venda_status' AND ss.sta_codigo=v.ven_status_venda
  SET v.ven_metodo_pagamento_id = sm.sta_id,
      v.ven_status_id = ss.sta_id;
      
ALTER TABLE tb_Vendas
  DROP COLUMN ven_metodo_pagamento,
  DROP COLUMN ven_status_venda;

ALTER TABLE tb_Vendas
  MODIFY ven_metodo_pagamento_id INT NOT NULL DEFAULT @sta_ven_metodo_default,
  MODIFY ven_status_id INT NOT NULL DEFAULT @sta_ven_status_default,
  ADD CONSTRAINT fk_ven_metodo_pagamento FOREIGN KEY (ven_metodo_pagamento_id) REFERENCES status_diversos(sta_id),
  ADD CONSTRAINT fk_ven_status FOREIGN KEY (ven_status_id) REFERENCES status_diversos(sta_id);

-- 8) Dados de auditoria (timestamps) nas principais tabelas.
ALTER TABLE tb_Usuarios
  ADD COLUMN created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD COLUMN updated_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

ALTER TABLE tb_Produtos
  ADD COLUMN created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD COLUMN updated_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

ALTER TABLE tb_Vendas
  ADD COLUMN created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD COLUMN updated_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

ALTER TABLE tb_Pedidos_Compra
  ADD COLUMN created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD COLUMN updated_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

ALTER TABLE tb_Lotes_Estoque
  ADD COLUMN created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD COLUMN updated_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

ALTER TABLE tb_Agendamentos
  ADD COLUMN created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD COLUMN updated_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

-- 9) Normalizacao de CPF/CNPJ: largura fixa para evitar formatos com mascara.
ALTER TABLE tb_Usuarios
  MODIFY usu_cpf_cnpj CHAR(14) COLLATE utf8mb4_unicode_ci NULL;

-- 10) Indices de apoio para buscas frequentes.
DROP INDEX IF EXISTS idx_lote_produto_validade ON tb_Lotes_Estoque;
ALTER TABLE tb_Lotes_Estoque ADD INDEX idx_lote_produto_validade (lot_id_produto, lot_data_validade);

DROP INDEX IF EXISTS idx_produto_nome ON tb_Produtos;
ALTER TABLE tb_Produtos ADD INDEX idx_produto_nome (pro_nome);

DROP INDEX IF EXISTS idx_item_produto ON tb_Itens_Venda;
ALTER TABLE tb_Itens_Venda ADD INDEX idx_item_produto (ite_id_produto);

COMMIT;

-- Consultas utilitarias pos-migracao
-- SELECT * FROM status_diversos ORDER BY sta_dominio, sta_codigo;
-- SELECT sta_codigo FROM status_diversos WHERE sta_dominio='venda_status';
