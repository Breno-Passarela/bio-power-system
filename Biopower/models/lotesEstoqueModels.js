const Database = require("../utils/database");

const banco = new Database();

class LotesEstoqueModels {
	#db;

	constructor() {
		this.#db = banco;
	}

	async obterEstoqueProduto(produtoId) {
		if (!produtoId) return 0;
		const rows = await this.#db.ExecutaComando(
			"SELECT COALESCE(SUM(lot_quantidade_atual), 0) AS estoque FROM tb_Lotes_Estoque WHERE lot_id_produto = ?",
			[produtoId],
		);
		return rows.length ? Number(rows[0].estoque || 0) : 0;
	}

	async ajustarEstoqueManual(produtoId, quantidade) {
		if (!produtoId) throw new Error("Produto inválido");
		const rows = await this.#db.ExecutaComando(
			"SELECT lot_id, lot_quantidade_atual FROM tb_Lotes_Estoque WHERE lot_id_produto = ? AND lot_numero_lote = 'AJUSTE-MANUAL' LIMIT 1",
			[produtoId],
		);

		if (rows.length) {
			const atual = Number(rows[0].lot_quantidade_atual || 0);
			const novoTotal = Math.max(atual + quantidade, 0);
			await this.#db.ExecutaComandoNonQuery(
				"UPDATE tb_Lotes_Estoque SET lot_quantidade_atual = ?, updated_at = CURRENT_TIMESTAMP WHERE lot_id = ?",
				[novoTotal, rows[0].lot_id],
			);
			return novoTotal;
		}

		const quantidadeInicial = Math.max(Number(quantidade) || 0, 0);
		await this.#db.ExecutaComandoLastInserted(
			"INSERT INTO tb_Lotes_Estoque (lot_id_produto, lot_numero_lote, lot_quantidade_atual, lot_data_validade) VALUES (?, 'AJUSTE-MANUAL', ?, '2099-12-31')",
			[produtoId, quantidadeInicial],
		);
		return quantidadeInicial;
	}
}

module.exports = LotesEstoqueModels;
