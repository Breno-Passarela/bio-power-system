const Database = require("../utils/database");

const banco = new Database();

class ServicosModels {
	#db;

	constructor() {
		this.#db = banco;
	}

	async listar() {
		const sql = `
			SELECT ser_id AS id, ser_nome AS nome, ser_descricao AS descricao, ser_preco AS preco
			FROM tb_Servicos
			ORDER BY ser_nome;
		`;
		const rows = await this.#db.ExecutaComando(sql, []);
		return rows.map((row) => ({
			id: row.id,
			nome: row.nome,
			descricao: row.descricao || "",
			preco: Number(row.preco || 0),
		}));
	}

	async criar({ nome, descricao, preco }) {
		if (!nome || preco === undefined || preco === null) throw new Error("Dados obrigatórios ausentes");
		const precoNumero = Number(preco);
		if (Number.isNaN(precoNumero)) throw new Error("Preço inválido");

		const sql = `
			INSERT INTO tb_Servicos (ser_nome, ser_descricao, ser_preco)
			VALUES (?, ?, ?);
		`;
		return this.#db.ExecutaComandoLastInserted(sql, [nome, descricao || null, precoNumero]);
	}

	async atualizar(id, { nome, descricao, preco }) {
		if (!id) throw new Error("Serviço inválido");
		const precoNumero = preco !== undefined && preco !== null ? Number(preco) : null;
		if (preco !== undefined && preco !== null && Number.isNaN(precoNumero)) throw new Error("Preço inválido");

		const sql = `
			UPDATE tb_Servicos
			SET ser_nome = COALESCE(?, ser_nome),
					ser_descricao = COALESCE(?, ser_descricao),
					ser_preco = COALESCE(?, ser_preco)
			WHERE ser_id = ?;
		`;
		return this.#db.ExecutaComandoNonQuery(sql, [nome || null, descricao || null, precoNumero, id]);
	}

	async deletar(id) {
		if (!id) return false;
		return this.#db.ExecutaComandoNonQuery("DELETE FROM tb_Servicos WHERE ser_id = ?", [id]);
	}
}

module.exports = ServicosModels;
