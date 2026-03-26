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
  `age_status_id` int NOT NULL DEFAULT '2',
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`age_id`),
  UNIQUE KEY `uq_agendamento_profissional` (`age_id_profissional`,`age_data_hora`),
  KEY `age_id_cliente` (`age_id_cliente`),
  KEY `age_id_tb_servico` (`age_id_servico`),
  KEY `fk_age_status` (`age_status_id`),
  CONSTRAINT `fk_age_status` FOREIGN KEY (`age_status_id`) REFERENCES `tb_status_diversos` (`sta_id`),
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
  `cat_nome` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`cat_id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Categorias`
--

LOCK TABLES `tb_Categorias` WRITE;
/*!40000 ALTER TABLE `tb_Categorias` DISABLE KEYS */;
INSERT INTO `tb_Categorias` VALUES (1,'Creatina'),(2,'Whey'),(3,'Pré-treino'),(4,'Termogênico'),(5,'Hipercalórico');
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
  `des_motivo` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
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
  `dev_motivo` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `dev_caminho_nota_fiscal` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `dev_status_id` int NOT NULL DEFAULT '5',
  PRIMARY KEY (`dev_id`),
  KEY `dev_id_venda` (`dev_id_venda`),
  KEY `fk_dev_status` (`dev_status_id`),
  CONSTRAINT `fk_dev_status` FOREIGN KEY (`dev_status_id`) REFERENCES `tb_status_diversos` (`sta_id`),
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
  `flu_tipo_id` int NOT NULL,
  `flu_valor` decimal(10,2) NOT NULL,
  `flu_data_movimentacao` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `flu_descricao` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `flu_origem_id` int DEFAULT NULL,
  `flu_origem_tipo` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`flu_id`),
  KEY `fk_flu_tipo` (`flu_tipo_id`),
  CONSTRAINT `fk_flu_tipo` FOREIGN KEY (`flu_tipo_id`) REFERENCES `tb_status_diversos` (`sta_id`)
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
  `for_razao_social` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `for_cnpj` varchar(18) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `for_contato` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
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
  KEY `idx_item_produto` (`ite_id_produto`),
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
  `lab_nome` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `lab_cnpj` varchar(18) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`lab_id`),
  UNIQUE KEY `lab_cnpj` (`lab_cnpj`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Laboratorios`
--

LOCK TABLES `tb_Laboratorios` WRITE;
/*!40000 ALTER TABLE `tb_Laboratorios` DISABLE KEYS */;
INSERT INTO `tb_Laboratorios` VALUES (1,'Growth',NULL),(2,'Integral Médica',NULL),(3,'DUX',NULL),(4,'Dark Lab',NULL),(5,'Black Skull',NULL),(6,'Max Titanium',NULL),(7,'Universal Nutrition',NULL),(8,'Iridium Labs',NULL),(9,'Probiótica',NULL),(10,'Cellucor',NULL),(11,'Integralmédica',NULL),(12,'BodyAction',NULL),(13,'Adaptogen Nutrition',NULL),(14,'TESTE MARCA',NULL),(15,'Eli Lilly',NULL);
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
  `lot_numero_lote` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `lot_quantidade_atual` int NOT NULL,
  `lot_data_validade` date NOT NULL,
  `lot_data_entrada` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `lot_id_fornecedor` int DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`lot_id`),
  KEY `lot_id_produto` (`lot_id_produto`),
  KEY `lot_id_fornecedor` (`lot_id_fornecedor`),
  KEY `idx_lote_produto_validade` (`lot_id_produto`,`lot_data_validade`),
  CONSTRAINT `tb_Lotes_Estoque_ibfk_1` FOREIGN KEY (`lot_id_produto`) REFERENCES `tb_Produtos` (`pro_id`) ON DELETE CASCADE,
  CONSTRAINT `tb_Lotes_Estoque_ibfk_2` FOREIGN KEY (`lot_id_fornecedor`) REFERENCES `tb_Fornecedores` (`for_id`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Lotes_Estoque`
--

LOCK TABLES `tb_Lotes_Estoque` WRITE;
/*!40000 ALTER TABLE `tb_Lotes_Estoque` DISABLE KEYS */;
INSERT INTO `tb_Lotes_Estoque` VALUES (1,1,'LOT-001',3,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(2,2,'LOT-002',47,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(3,3,'LOT-003',22,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(5,5,'LOT-005',6,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(6,6,'LOT-006',31,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(7,7,'LOT-007',8,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(8,8,'LOT-008',19,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(9,9,'LOT-009',2,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(10,10,'LOT-010',40,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(11,11,'LOT-011',12,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(12,12,'LOT-012',0,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(13,13,'LOT-013',28,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(14,14,'LOT-014',5,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(15,15,'LOT-015',16,'2026-12-31','2026-03-25 19:41:26',NULL,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(16,12,'AJUSTE-MANUAL',4,'2099-12-31','2026-03-26 11:58:10',NULL,'2026-03-26 11:58:10','2026-03-26 11:58:10');
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
  `ped_status_id` int NOT NULL DEFAULT '10',
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ped_id`),
  KEY `ped_id_fornecedor` (`ped_id_fornecedor`),
  KEY `ped_id_responsavel` (`ped_id_responsavel`),
  KEY `fk_ped_status` (`ped_status_id`),
  CONSTRAINT `fk_ped_status` FOREIGN KEY (`ped_status_id`) REFERENCES `tb_status_diversos` (`sta_id`),
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
  `pro_nome` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `pro_descricao` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `pro_preco_venda` decimal(10,2) NOT NULL,
  `pro_id_categoria` int DEFAULT NULL,
  `pro_id_laboratorio` int DEFAULT NULL,
  `pro_porcentagem_promocao` decimal(5,2) DEFAULT '0.00',
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`pro_id`),
  KEY `pro_id_laboratorio` (`pro_id_laboratorio`),
  KEY `idx_produto_categoria` (`pro_id_categoria`),
  KEY `idx_produto_nome` (`pro_nome`),
  CONSTRAINT `tb_Produtos_ibfk_1` FOREIGN KEY (`pro_id_categoria`) REFERENCES `tb_Categorias` (`cat_id`) ON DELETE SET NULL,
  CONSTRAINT `tb_Produtos_ibfk_2` FOREIGN KEY (`pro_id_laboratorio`) REFERENCES `tb_Laboratorios` (`lab_id`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Produtos`
--

LOCK TABLES `tb_Produtos` WRITE;
/*!40000 ALTER TABLE `tb_Produtos` DISABLE KEYS */;
INSERT INTO `tb_Produtos` VALUES (1,'Creatina Monohidratada 250g','Em breve',79.92,1,1,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(2,'Whey Protein Baunilha 900g','Em breve',129.90,2,2,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(3,'Pré-Treino Explosivo DUX 300g','Em breve',98.50,3,3,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(5,'Termogênico Black Skull 60 caps','Em breve',59.90,4,5,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(6,'Whey Protein Chocolate 1kg','Em breve',134950.00,2,6,0.00,'2026-03-25 19:41:26','2026-03-26 14:43:18'),(7,'Pré-Treino Insano 280g','Em breve',89.99,3,5,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(8,'Creatina Universal 300g','Em breve',109.90,1,7,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(9,'Termogênico Kimera 60 caps','Em breve',69.90,4,8,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(10,'Whey Blend 3W 900g','Em breve',119.00,2,9,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(11,'Pré-Treino C4 Original 195g','Em breve',139.90,3,10,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(12,'Creatina Hardcore Reload 300g','Em breve',94.90,1,11,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(13,'Termogênico Thermo Flame 120 caps','Em breve',79.90,4,12,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(14,'Whey Isolado 900g','Em breve',189.90,2,3,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26'),(15,'Pré-Treino Psycho 280g','Em breve',84.50,3,13,0.00,'2026-03-25 19:41:26','2026-03-25 19:41:26');
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
  `ser_nome` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `ser_descricao` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `ser_preco` decimal(10,2) NOT NULL,
  PRIMARY KEY (`ser_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Servicos`
--

LOCK TABLES `tb_Servicos` WRITE;
/*!40000 ALTER TABLE `tb_Servicos` DISABLE KEYS */;
INSERT INTO `tb_Servicos` VALUES (1,'Avaliação Física e Composição Corporal','Avaliação completa da composição corporal do cliente, com foco em análise física e acompanhamento de evolução. O serviço pode incluir bioimpedância, avaliação de dobras cutâneas, perímetros corporais e observações gerais sobre condicionamento físico. Ideal para quem deseja iniciar um plano de treino, suplementação ou reeducação alimentar com mais precisão.',200.00),(2,'Consulta Nutricional Inicial','Atendimento inicial voltado para acolhimento, anamnese nutricional e entendimento da rotina do cliente. Durante a consulta, são avaliados hábitos alimentares, objetivos, dificuldades e preferências, permitindo a criação de um plano alimentar básico e mais alinhado à realidade do paciente.',180.00),(3,'Montagem de Stack Personalizada de Suplementos','Serviço de recomendação estratégica de suplementação com base no objetivo do cliente. A montagem pode ser direcionada para ganho de massa muscular, perda de gordura, melhora de performance, disposição, recuperação ou saúde geral, sempre considerando perfil, rotina e necessidades individuais.',120.00),(4,'Acompanhamento Nutricional e de Suplementação','Acompanhamento contínuo para revisão de resultados, evolução do cliente e ajustes no plano alimentar e na suplementação. Ideal para quem busca constância, monitoramento profissional e melhor adaptação ao longo do processo.',250.00),(5,'Orientação Nutricional Pré e Pós-Treino','Atendimento focado em orientar o cliente sobre estratégias nutricionais e suplementares antes e após o treino. O objetivo é melhorar desempenho, recuperação muscular, energia e aproveitamento nutricional de acordo com a rotina de treinos.',90.00),(6,'Análise de Exames e Suplementação Coadjuvante','Serviço de análise complementar de exames laboratoriais apresentados pelo cliente, com foco em identificar possíveis necessidades nutricionais e sugerir suplementação coadjuvante quando aplicável. Ideal para tornar o acompanhamento mais individualizado e estratégico.',200.00),(7,'Plano Corporativo ou Equipe Esportiva','Pacote voltado para empresas, grupos, academias ou equipes esportivas que desejam acompanhamento nutricional e orientação em suplementação de forma coletiva. Pode incluir avaliação inicial, direcionamento alimentar, suporte estratégico e ações voltadas à performance e bem-estar do grupo.',800.00),(8,'Workshop ou Mini-Palestra sobre Nutrição e Suplementação','Encontro educativo voltado para orientação prática sobre temas como suplementação, hidratação, recuperação muscular, alimentação no esporte e saúde geral. Ideal para academias, empresas, grupos esportivos ou ações de educação em saúde.',350.00);
/*!40000 ALTER TABLE `tb_Servicos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Servicos_Contratados`
--

DROP TABLE IF EXISTS `tb_Servicos_Contratados`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Servicos_Contratados` (
  `sc_id` int NOT NULL AUTO_INCREMENT,
  `sc_id_cliente` int NOT NULL,
  `sc_id_servico` int NOT NULL,
  `sc_status` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT 'pendente',
  `sc_observacoes` text COLLATE utf8mb4_unicode_ci,
  `sc_data_contratacao` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `sc_data_atualizacao` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`sc_id`),
  KEY `idx_sc_cliente` (`sc_id_cliente`),
  KEY `idx_sc_servico` (`sc_id_servico`),
  CONSTRAINT `fk_sc_cliente` FOREIGN KEY (`sc_id_cliente`) REFERENCES `tb_Usuarios` (`usu_id`) ON DELETE CASCADE,
  CONSTRAINT `fk_sc_servico` FOREIGN KEY (`sc_id_servico`) REFERENCES `tb_Servicos` (`ser_id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Servicos_Contratados`
--

LOCK TABLES `tb_Servicos_Contratados` WRITE;
/*!40000 ALTER TABLE `tb_Servicos_Contratados` DISABLE KEYS */;
INSERT INTO `tb_Servicos_Contratados` VALUES (1,1,1,'finalizado',NULL,'2026-03-26 12:50:43','2026-03-26 13:54:57'),(2,1,7,'em_andamento',NULL,'2026-03-26 13:21:27','2026-03-26 13:54:36'),(3,6,4,'pendente',NULL,'2026-03-26 13:32:52','2026-03-26 13:32:52'),(4,6,6,'aprovado',NULL,'2026-03-26 13:33:02','2026-03-26 13:54:19');
/*!40000 ALTER TABLE `tb_Servicos_Contratados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_Usuarios`
--

DROP TABLE IF EXISTS `tb_Usuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_Usuarios` (
  `usu_id` int NOT NULL AUTO_INCREMENT,
  `usu_nome` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `usu_email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `usu_senha` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `usu_cpf_cnpj` char(14) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `usu_typ_id` int NOT NULL,
  `usu_ativo` tinyint(1) NOT NULL DEFAULT '1',
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`usu_id`),
  UNIQUE KEY `usu_email` (`usu_email`),
  UNIQUE KEY `usu_cpf_cnpj` (`usu_cpf_cnpj`),
  KEY `usu_typ_id` (`usu_typ_id`),
  CONSTRAINT `tb_Usuarios_ibfk_1` FOREIGN KEY (`usu_typ_id`) REFERENCES `tb_typeUser` (`typ_id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_Usuarios`
--

LOCK TABLES `tb_Usuarios` WRITE;
/*!40000 ALTER TABLE `tb_Usuarios` DISABLE KEYS */;
INSERT INTO `tb_Usuarios` VALUES (1,'Breno','breno@gmail.com','123456','12345678900',1,1,'2026-03-25 14:42:42','2026-03-25 14:42:42'),(2,'Almeida','almeida@biopower.com','admin123','11111111111',1,1,'2026-03-25 17:19:29','2026-03-25 17:19:29'),(3,'Mariana Souza','mariana.souza@biopower.com','admin123','22222222222',1,1,'2026-03-25 17:20:57','2026-03-25 17:20:57'),(4,'Carlos Pereira','carlos.pereira@biopower.com','func123','33333333333',2,1,'2026-03-25 17:20:57','2026-03-25 17:20:57'),(5,'Fernanda Lima','fernanda.lima@biopower.com','func123','44444444444',2,1,'2026-03-25 17:20:57','2026-03-25 17:20:57'),(6,'João Silva','joao.silva@biopower.com','cliente123','55555555555',3,1,'2026-03-25 17:20:57','2026-03-25 17:20:57'),(7,'Ana Paula','ana.paula@biopower.com','cliente123','66666666666',3,1,'2026-03-25 17:20:57','2026-03-25 17:20:57'),(8,'Ricardo Mendes','ricardo.mendes@biopower.com','cliente123','77777777777',3,0,'2026-03-25 17:20:57','2026-03-25 17:20:57'),(9,'Assis','assis@biopower.com','123456','12345678998',1,0,'2026-03-26 14:08:33','2026-03-26 14:08:45'),(11,'Breno Passarela','passarela@gmail.com','123456','70934896321',1,0,'2026-03-26 14:18:08','2026-03-26 14:43:53'),(12,'Breno H','brenof@gmail.com','123456','462.709.348-93',2,1,'2026-03-26 14:39:37','2026-03-26 14:39:37');
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
  `ven_metodo_pagamento_id` int NOT NULL DEFAULT '13',
  `ven_status_id` int NOT NULL DEFAULT '17',
  `ven_endereco_entrega` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `ven_frete` decimal(10,2) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ven_id`),
  KEY `ven_id_cliente` (`ven_id_cliente`),
  KEY `fk_ven_metodo_pagamento` (`ven_metodo_pagamento_id`),
  KEY `fk_ven_status` (`ven_status_id`),
  CONSTRAINT `fk_ven_metodo_pagamento` FOREIGN KEY (`ven_metodo_pagamento_id`) REFERENCES `tb_status_diversos` (`sta_id`),
  CONSTRAINT `fk_ven_status` FOREIGN KEY (`ven_status_id`) REFERENCES `tb_status_diversos` (`sta_id`),
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
-- Table structure for table `tb_status_diversos`
--

DROP TABLE IF EXISTS `tb_status_diversos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_status_diversos` (
  `sta_id` int NOT NULL AUTO_INCREMENT,
  `sta_dominio` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `sta_codigo` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `sta_descricao` varchar(120) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`sta_id`),
  UNIQUE KEY `uq_status_dominio_codigo` (`sta_dominio`,`sta_codigo`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_status_diversos`
--

LOCK TABLES `tb_status_diversos` WRITE;
/*!40000 ALTER TABLE `tb_status_diversos` DISABLE KEYS */;
INSERT INTO `tb_status_diversos` VALUES (1,'agendamento_status','CONFIRMADO','Agendamento confirmado'),(2,'agendamento_status','AGUARDANDO_PAGAMENTO','Aguardando pagamento'),(3,'agendamento_status','CANCELADO','Agendamento cancelado'),(4,'agendamento_status','CONCLUIDO','Agendamento concluido'),(5,'devolucao_status','PENDENTE','Aguardando avaliacao'),(6,'devolucao_status','APROVADO','Devolucao aprovada'),(7,'devolucao_status','RECUSADO','Devolucao recusada'),(8,'fluxo_caixa_tipo','RECEITA','Entrada de recursos'),(9,'fluxo_caixa_tipo','DESPESA','Saida de recursos'),(10,'pedido_status','SOLICITADO','Pedido solicitado'),(11,'pedido_status','EM_ANDAMENTO','Pedido em andamento'),(12,'pedido_status','CONCLUIDO','Pedido concluido'),(13,'venda_metodo_pagamento','PIX','Pagamento via PIX'),(14,'venda_metodo_pagamento','CREDITO','Cartao de credito'),(15,'venda_metodo_pagamento','DEBITO','Cartao de debito'),(16,'venda_metodo_pagamento','BOLETO','Pagamento por boleto'),(17,'venda_status','AGUARDANDO','Aguardando pagamento'),(18,'venda_status','PAGO','Pagamento confirmado'),(19,'venda_status','CANCELADO','Venda cancelada');
/*!40000 ALTER TABLE `tb_status_diversos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_typeUser`
--

DROP TABLE IF EXISTS `tb_typeUser`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tb_typeUser` (
  `typ_id` int NOT NULL AUTO_INCREMENT,
  `typ_descricao` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
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

-- Dump completed on 2026-03-26 13:38:35
