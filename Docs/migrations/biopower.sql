CREATE DATABASE  IF NOT EXISTS `bio_sys_db` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `bio_sys_db`;
-- MySQL dump 10.13  Distrib 8.0.45, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: bio_sys_db
-- ------------------------------------------------------
-- Server version	8.0.33

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `tb_Agendamentos`
--

DROP TABLE IF EXISTS `tb_Agendamentos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Agendamentos` (
  `age_id` int NOT NULL AUTO_INCREMENT,
  `age_id_cliente` int NOT NULL,
  `age_id_profissional` int NOT NULL,
  `age_id_servico` int NOT NULL,
  `age_data_hora` datetime NOT NULL,
  `age_status` enum('CONFIRMADO','AGUARDANDO_PAGAMENTO','CANCELADO','CONCLUIDO') COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`age_id`),
  UNIQUE KEY `uq_agendamento_profissional` (`age_id_profissional`,`age_data_hora`),
  KEY `age_id_cliente` (`age_id_cliente`),
  KEY `age_id_servico` (`age_id_servico`),
  CONSTRAINT `tb_Agendamentos_ibfk_1` FOREIGN KEY (`age_id_cliente`) REFERENCES `tb_Usuarios` (`usu_id`),
  CONSTRAINT `tb_Agendamentos_ibfk_2` FOREIGN KEY (`age_id_profissional`) REFERENCES `tb_Usuarios` (`usu_id`),
  CONSTRAINT `tb_Agendamentos_ibfk_3` FOREIGN KEY (`age_id_servico`) REFERENCES `tb_Servicos` (`ser_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Agendamentos`
--

LOCK TABLES `tb_Agendamentos` WRITE;
/*!40000 ALTER TABLE `tb_Agendamentos` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Agendamentos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Categorias`
--

DROP TABLE IF EXISTS `tb_Categorias`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Categorias` (
  `cat_id` int NOT NULL AUTO_INCREMENT,
  `cat_nome` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`cat_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Categorias`
--

LOCK TABLES `tb_Categorias` WRITE;
/*!40000 ALTER TABLE `tb_Categorias` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Categorias` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Descartes`
--

DROP TABLE IF EXISTS `tb_Descartes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Descartes` (
  `des_id` int NOT NULL AUTO_INCREMENT,
  `des_id_lote` int NOT NULL,
  `des_quantidade` int NOT NULL,
  `des_motivo` text COLLATE utf8mb4_unicode_ci,
  `des_data_descarte` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `des_id_responsavel` int NOT NULL,
  PRIMARY KEY (`des_id`),
  KEY `des_id_lote` (`des_id_lote`),
  KEY `des_id_responsavel` (`des_id_responsavel`),
  CONSTRAINT `tb_Descartes_ibfk_1` FOREIGN KEY (`des_id_lote`) REFERENCES `tb_Lotes_Estoque` (`lot_id`),
  CONSTRAINT `tb_Descartes_ibfk_2` FOREIGN KEY (`des_id_responsavel`) REFERENCES `tb_Usuarios` (`usu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Descartes`
--

LOCK TABLES `tb_Descartes` WRITE;
/*!40000 ALTER TABLE `tb_Descartes` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Descartes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Devolucoes`
--

DROP TABLE IF EXISTS `tb_Devolucoes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Devolucoes` (
  `dev_id` int NOT NULL AUTO_INCREMENT,
  `dev_id_venda` int NOT NULL,
  `dev_motivo` text COLLATE utf8mb4_unicode_ci,
  `dev_caminho_nota_fiscal` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `dev_status` enum('PENDENTE','APROVADO','RECUSADO') COLLATE utf8mb4_unicode_ci DEFAULT 'PENDENTE',
  PRIMARY KEY (`dev_id`),
  KEY `dev_id_venda` (`dev_id_venda`),
  CONSTRAINT `tb_Devolucoes_ibfk_1` FOREIGN KEY (`dev_id_venda`) REFERENCES `tb_Vendas` (`ven_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Devolucoes`
--

LOCK TABLES `tb_Devolucoes` WRITE;
/*!40000 ALTER TABLE `tb_Devolucoes` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Devolucoes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Fluxo_Caixa`
--

DROP TABLE IF EXISTS `tb_Fluxo_Caixa`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Fluxo_Caixa` (
  `flu_id` int NOT NULL AUTO_INCREMENT,
  `flu_tipo` enum('RECEITA','DESPESA') COLLATE utf8mb4_unicode_ci NOT NULL,
  `flu_valor` decimal(10,2) NOT NULL,
  `flu_data_movimentacao` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `flu_descricao` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `flu_origem_id` int DEFAULT NULL,
  `flu_origem_tipo` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`flu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Fluxo_Caixa`
--

LOCK TABLES `tb_Fluxo_Caixa` WRITE;
/*!40000 ALTER TABLE `tb_Fluxo_Caixa` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Fluxo_Caixa` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Fornecedores`
--

DROP TABLE IF EXISTS `tb_Fornecedores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Fornecedores` (
  `for_id` int NOT NULL AUTO_INCREMENT,
  `for_razao_social` varchar(150) COLLATE utf8mb4_unicode_ci NOT NULL,
  `for_cnpj` varchar(18) COLLATE utf8mb4_unicode_ci NOT NULL,
  `for_contato` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`for_id`),
  UNIQUE KEY `for_cnpj` (`for_cnpj`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Fornecedores`
--

LOCK TABLES `tb_Fornecedores` WRITE;
/*!40000 ALTER TABLE `tb_Fornecedores` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Fornecedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Itens_Pedido_Compra`
--

DROP TABLE IF EXISTS `tb_Itens_Pedido_Compra`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Itens_Pedido_Compra` (
  `ipc_id` int NOT NULL AUTO_INCREMENT,
  `ipc_id_pedido` int NOT NULL,
  `ipc_id_produto` int NOT NULL,
  `ipc_quantidade` int NOT NULL,
  `ipc_preco_unitario` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`ipc_id`),
  KEY `ipc_id_pedido` (`ipc_id_pedido`),
  KEY `ipc_id_produto` (`ipc_id_produto`),
  CONSTRAINT `tb_Itens_Pedido_Compra_ibfk_1` FOREIGN KEY (`ipc_id_pedido`) REFERENCES `tb_Pedidos_Compra` (`ped_id`) ON DELETE CASCADE,
  CONSTRAINT `tb_Itens_Pedido_Compra_ibfk_2` FOREIGN KEY (`ipc_id_produto`) REFERENCES `tb_Produtos` (`pro_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Itens_Pedido_Compra`
--

LOCK TABLES `tb_Itens_Pedido_Compra` WRITE;
/*!40000 ALTER TABLE `tb_Itens_Pedido_Compra` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Itens_Pedido_Compra` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Itens_Venda`
--

DROP TABLE IF EXISTS `tb_Itens_Venda`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Itens_Venda` (
  `ite_id` int NOT NULL AUTO_INCREMENT,
  `ite_id_venda` int NOT NULL,
  `ite_id_produto` int NOT NULL,
  `ite_quantidade` int NOT NULL,
  `ite_preco_unitario` decimal(10,2) NOT NULL,
  `ite_id_lote` int DEFAULT NULL,
  PRIMARY KEY (`ite_id`),
  KEY `ite_id_venda` (`ite_id_venda`),
  KEY `ite_id_produto` (`ite_id_produto`),
  KEY `fk_item_lote` (`ite_id_lote`),
  CONSTRAINT `fk_item_lote` FOREIGN KEY (`ite_id_lote`) REFERENCES `tb_Lotes_Estoque` (`lot_id`),
  CONSTRAINT `tb_Itens_Venda_ibfk_1` FOREIGN KEY (`ite_id_venda`) REFERENCES `tb_Vendas` (`ven_id`) ON DELETE CASCADE,
  CONSTRAINT `tb_Itens_Venda_ibfk_2` FOREIGN KEY (`ite_id_produto`) REFERENCES `tb_Produtos` (`pro_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Itens_Venda`
--

LOCK TABLES `tb_Itens_Venda` WRITE;
/*!40000 ALTER TABLE `tb_Itens_Venda` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Itens_Venda` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Laboratorios`
--

DROP TABLE IF EXISTS `tb_Laboratorios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Laboratorios` (
  `lab_id` int NOT NULL AUTO_INCREMENT,
  `lab_nome` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `lab_cnpj` varchar(18) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`lab_id`),
  UNIQUE KEY `lab_cnpj` (`lab_cnpj`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Laboratorios`
--

LOCK TABLES `tb_Laboratorios` WRITE;
/*!40000 ALTER TABLE `tb_Laboratorios` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Laboratorios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Lotes_Estoque`
--

DROP TABLE IF EXISTS `tb_Lotes_Estoque`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Lotes_Estoque` (
  `lot_id` int NOT NULL AUTO_INCREMENT,
  `lot_id_produto` int NOT NULL,
  `lot_numero_lote` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `lot_quantidade_atual` int NOT NULL,
  `lot_data_validade` date NOT NULL,
  `lot_data_entrada` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `lot_id_fornecedor` int DEFAULT NULL,
  PRIMARY KEY (`lot_id`),
  KEY `lot_id_produto` (`lot_id_produto`),
  KEY `lot_id_fornecedor` (`lot_id_fornecedor`),
  CONSTRAINT `tb_Lotes_Estoque_ibfk_1` FOREIGN KEY (`lot_id_produto`) REFERENCES `tb_Produtos` (`pro_id`) ON DELETE CASCADE,
  CONSTRAINT `tb_Lotes_Estoque_ibfk_2` FOREIGN KEY (`lot_id_fornecedor`) REFERENCES `tb_Fornecedores` (`for_id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Lotes_Estoque`
--

LOCK TABLES `tb_Lotes_Estoque` WRITE;
/*!40000 ALTER TABLE `tb_Lotes_Estoque` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Lotes_Estoque` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Pedidos_Compra`
--

DROP TABLE IF EXISTS `tb_Pedidos_Compra`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Pedidos_Compra` (
  `ped_id` int NOT NULL AUTO_INCREMENT,
  `ped_id_fornecedor` int NOT NULL,
  `ped_id_responsavel` int NOT NULL,
  `ped_data_pedido` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `ped_prazo_entrega_previsto` date DEFAULT NULL,
  `ped_status` enum('SOLICITADO','EM_ANDAMENTO','CONCLUIDO') COLLATE utf8mb4_unicode_ci DEFAULT 'SOLICITADO',
  PRIMARY KEY (`ped_id`),
  KEY `ped_id_fornecedor` (`ped_id_fornecedor`),
  KEY `ped_id_responsavel` (`ped_id_responsavel`),
  CONSTRAINT `tb_Pedidos_Compra_ibfk_1` FOREIGN KEY (`ped_id_fornecedor`) REFERENCES `tb_Fornecedores` (`for_id`),
  CONSTRAINT `tb_Pedidos_Compra_ibfk_2` FOREIGN KEY (`ped_id_responsavel`) REFERENCES `tb_Usuarios` (`usu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Pedidos_Compra`
--

LOCK TABLES `tb_Pedidos_Compra` WRITE;
/*!40000 ALTER TABLE `tb_Pedidos_Compra` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Pedidos_Compra` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Produto_Fornecedores`
--

DROP TABLE IF EXISTS `tb_Produto_Fornecedores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Produto_Fornecedores` (
  `pf_id_produto` int NOT NULL,
  `pf_id_fornecedor` int NOT NULL,
  `pf_preco_compra` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`pf_id_produto`,`pf_id_fornecedor`),
  KEY `pf_id_fornecedor` (`pf_id_fornecedor`),
  CONSTRAINT `tb_Produto_Fornecedores_ibfk_1` FOREIGN KEY (`pf_id_produto`) REFERENCES `tb_Produtos` (`pro_id`) ON DELETE CASCADE,
  CONSTRAINT `tb_Produto_Fornecedores_ibfk_2` FOREIGN KEY (`pf_id_fornecedor`) REFERENCES `tb_Fornecedores` (`for_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Produto_Fornecedores`
--

LOCK TABLES `tb_Produto_Fornecedores` WRITE;
/*!40000 ALTER TABLE `tb_Produto_Fornecedores` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Produto_Fornecedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Produtos`
--

DROP TABLE IF EXISTS `tb_Produtos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Produtos` (
  `pro_id` int NOT NULL AUTO_INCREMENT,
  `pro_nome` varchar(150) COLLATE utf8mb4_unicode_ci NOT NULL,
  `pro_descricao` text COLLATE utf8mb4_unicode_ci,
  `pro_preco_venda` decimal(10,2) NOT NULL,
  `pro_id_categoria` int DEFAULT NULL,
  `pro_id_laboratorio` int DEFAULT NULL,
  `pro_porcentagem_promocao` decimal(5,2) DEFAULT '0.00',
  PRIMARY KEY (`pro_id`),
  KEY `pro_id_laboratorio` (`pro_id_laboratorio`),
  KEY `idx_produto_categoria` (`pro_id_categoria`),
  CONSTRAINT `tb_Produtos_ibfk_1` FOREIGN KEY (`pro_id_categoria`) REFERENCES `tb_Categorias` (`cat_id`) ON DELETE SET NULL,
  CONSTRAINT `tb_Produtos_ibfk_2` FOREIGN KEY (`pro_id_laboratorio`) REFERENCES `tb_Laboratorios` (`lab_id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Produtos`
--

LOCK TABLES `tb_Produtos` WRITE;
/*!40000 ALTER TABLE `tb_Produtos` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Produtos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Servicos`
--

DROP TABLE IF EXISTS `tb_Servicos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Servicos` (
  `ser_id` int NOT NULL AUTO_INCREMENT,
  `ser_nome` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `ser_descricao` text COLLATE utf8mb4_unicode_ci,
  `ser_preco` decimal(10,2) NOT NULL,
  PRIMARY KEY (`ser_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Servicos`
--

LOCK TABLES `tb_Servicos` WRITE;
/*!40000 ALTER TABLE `tb_Servicos` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Servicos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Usuarios`
--

DROP TABLE IF EXISTS `tb_Usuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Usuarios` (
  `usu_id` int NOT NULL AUTO_INCREMENT,
  `usu_nome` varchar(150) COLLATE utf8mb4_unicode_ci NOT NULL,
  `usu_email` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `usu_senha` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `usu_cpf_cnpj` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `usu_typ_id` int NOT NULL,
  PRIMARY KEY (`usu_id`),
  UNIQUE KEY `usu_email` (`usu_email`),
  UNIQUE KEY `usu_cpf_cnpj` (`usu_cpf_cnpj`),
  KEY `usu_typ_id` (`usu_typ_id`),
  CONSTRAINT `tb_Usuarios_ibfk_1` FOREIGN KEY (`usu_typ_id`) REFERENCES `tb_typeUser` (`typ_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Usuarios`
--

LOCK TABLES `tb_Usuarios` WRITE;
/*!40000 ALTER TABLE `tb_Usuarios` DISABLE KEYS */;
INSERT INTO `tb_Usuarios` VALUES (1,'Breno','breno@gmail.com','123456','12345678900',1);
/*!40000 ALTER TABLE `tb_Usuarios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Vendas`
--

DROP TABLE IF EXISTS `tb_Vendas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Vendas` (
  `ven_id` int NOT NULL AUTO_INCREMENT,
  `ven_id_cliente` int NOT NULL,
  `ven_data_venda` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `ven_valor_total` decimal(10,2) NOT NULL,
  `ven_metodo_pagamento` enum('PIX','CREDITO','DEBITO','BOLETO') COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `ven_status_venda` enum('AGUARDANDO','PAGO','CANCELADO') COLLATE utf8mb4_unicode_ci DEFAULT 'AGUARDANDO',
  `ven_endereco_entrega` text COLLATE utf8mb4_unicode_ci,
  `ven_frete` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`ven_id`),
  KEY `ven_id_cliente` (`ven_id_cliente`),
  CONSTRAINT `tb_Vendas_ibfk_1` FOREIGN KEY (`ven_id_cliente`) REFERENCES `tb_Usuarios` (`usu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Vendas`
--

LOCK TABLES `tb_Vendas` WRITE;
/*!40000 ALTER TABLE `tb_Vendas` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_Vendas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_typeUser`
--

DROP TABLE IF EXISTS `tb_typeUser`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_typeUser` (
  `typ_id` int NOT NULL AUTO_INCREMENT,
  `typ_descricao` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`typ_id`),
  UNIQUE KEY `typ_descricao` (`typ_descricao`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_typeUser`
--

LOCK TABLES `tb_typeUser` WRITE;
/*!40000 ALTER TABLE `tb_typeUser` DISABLE KEYS */;
INSERT INTO `tb_typeUser` VALUES (1,'Administrador'),(3,'Cliente'),(2,'Funcionario');
/*!40000 ALTER TABLE `tb_typeUser` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'bio_sys_db'
--

--
-- Dumping routines for database 'bio_sys_db'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-03-10  8:54:34
