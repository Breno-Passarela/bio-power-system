const Database = require("../utils/database");

const banco = new Database();

class ServicosContratadosModels {
  #db;

  constructor() {
    this.#db = banco;
  }

  async criar({ clienteId, servicoId, status = "pendente", observacoes = null }) {
    const sql = `
      INSERT INTO tb_Servicos_Contratados
        (sc_id_cliente, sc_id_servico, sc_status, sc_observacoes, sc_data_contratacao)
      VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP);
    `;
    return this.#db.ExecutaComandoLastInserted(sql, [clienteId, servicoId, status, observacoes]);
  }

  async listarPorCliente(clienteId) {
    if (!clienteId) return [];
    const sql = `
      SELECT
        sc.sc_id AS id,
        sc.sc_status AS status,
        sc.sc_data_contratacao AS dataContratacao,
        sc.sc_data_atualizacao AS dataAtualizacao,
        sc.sc_observacoes AS observacoes,
        s.ser_nome AS servicoNome,
        s.ser_descricao AS servicoDescricao,
        s.ser_preco AS servicoPreco
      FROM tb_Servicos_Contratados sc
      INNER JOIN tb_Servicos s ON s.ser_id = sc.sc_id_servico
      WHERE sc.sc_id_cliente = ?
      ORDER BY sc.sc_data_contratacao DESC;
    `;
    const rows = await this.#db.ExecutaComando(sql, [clienteId]);
    return rows.map((row) => ({
      id: row.id,
      status: row.status,
      dataContratacao: row.dataContratacao,
      dataAtualizacao: row.dataAtualizacao,
      observacoes: row.observacoes,
      servicoNome: row.servicoNome,
      servicoDescricao: row.servicoDescricao,
      servicoPreco: Number(row.servicoPreco || 0),
    }));
  }

  async listarTodos(filtro = {}) {
    const { status } = filtro;
    const params = [];
    const where = [];

    if (status) {
      where.push("sc.sc_status = ?");
      params.push(status);
    }

    const sql = `
      SELECT
        sc.sc_id AS id,
        sc.sc_status AS status,
        sc.sc_data_contratacao AS dataContratacao,
        sc.sc_data_atualizacao AS dataAtualizacao,
        sc.sc_observacoes AS observacoes,
        s.ser_nome AS servicoNome,
        s.ser_preco AS servicoPreco,
        s.ser_descricao AS servicoDescricao,
        u.usu_nome AS clienteNome,
        u.usu_email AS clienteEmail,
        u.usu_id AS clienteId
      FROM tb_Servicos_Contratados sc
      INNER JOIN tb_Servicos s ON s.ser_id = sc.sc_id_servico
      INNER JOIN tb_Usuarios u ON u.usu_id = sc.sc_id_cliente
      ${where.length ? `WHERE ${where.join(" AND ")}` : ""}
      ORDER BY sc.sc_data_contratacao DESC;
    `;

    const rows = await this.#db.ExecutaComando(sql, params);
    return rows.map((row) => ({
      id: row.id,
      status: row.status,
      dataContratacao: row.dataContratacao,
      dataAtualizacao: row.dataAtualizacao,
      observacoes: row.observacoes,
      servicoNome: row.servicoNome,
      servicoDescricao: row.servicoDescricao,
      servicoPreco: Number(row.servicoPreco || 0),
      clienteNome: row.clienteNome,
      clienteEmail: row.clienteEmail,
      clienteId: row.clienteId,
    }));
  }

  async atualizarStatus(id, { status, observacoes }) {
    if (!id || !status) return null;

    const campos = ["sc_status = ?", "sc_data_atualizacao = CURRENT_TIMESTAMP"];
    const params = [status];

    if (observacoes !== undefined) {
      campos.push("sc_observacoes = ?");
      params.push(observacoes);
    }

    params.push(id);

    const sql = `
      UPDATE tb_Servicos_Contratados
      SET ${campos.join(", ")}
      WHERE sc_id = ?;
    `;

    return this.#db.ExecutaComandoNonQuery(sql, params);
  }
}

module.exports = ServicosContratadosModels;
