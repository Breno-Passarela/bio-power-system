const Database = require("../utils/database");

const banco = new Database();

class ProdutosModels {
  #db;

  constructor() {
    this.#db = banco;
  }

  static #formatCurrency(valor) {
    const numero = Number(valor || 0);
    return numero.toLocaleString("pt-BR", { style: "currency", currency: "BRL" });
  }

  static parseCurrencyToNumber(valor) {
    if (valor === undefined || valor === null) return 0;
    const normalizado = String(valor).replace(/[^\d,-]/g, "").replace(",", ".");
    const numero = parseFloat(normalizado);
    return Number.isNaN(numero) ? 0 : numero;
  }

  async listarParaInterface() {
    const sql = `
      SELECT
        p.pro_id AS id,
        p.pro_nome AS nome,
        p.pro_descricao AS descricao,
        p.pro_preco_venda AS preco,
        p.pro_porcentagem_promocao AS desconto,
        c.cat_nome AS categoria,
        l.lab_nome AS marca,
        COALESCE(le.estoque, 0) AS estoque
      FROM tb_Produtos p
      LEFT JOIN tb_Categorias c ON c.cat_id = p.pro_id_categoria
      LEFT JOIN tb_Laboratorios l ON l.lab_id = p.pro_id_laboratorio
      LEFT JOIN (
        SELECT lot_id_produto, SUM(lot_quantidade_atual) AS estoque
        FROM tb_Lotes_Estoque
        GROUP BY lot_id_produto
      ) le ON le.lot_id_produto = p.pro_id
      ORDER BY p.pro_nome;
    `;

    const rows = await this.#db.ExecutaComando(sql, []);

    return rows.map((row, index) => this.#mapRowToView(row, index));
  }

  #mapRowToView(row, index = 0) {
    const precoNumber = Number(row.preco || 0);
    const descontoNumero = Number(row.desconto || 0);
    const temDesconto = descontoNumero > 0;

    return {
      id: row.id,
      index,
      nome: row.nome,
      descricao: row.descricao,
      preco: ProdutosModels.#formatCurrency(precoNumber),
      precoNumber,
      categoria: row.categoria || "Sem categoria",
      marca: row.marca || "Sem marca",
      sabor: row.descricao || "Sem sabor",
      desconto: temDesconto ? `${descontoNumero}%` : "",
      credito: "",
      imagem: "/assets/imgs/product/default.png",
      alt: row.nome,
      estoque: Number(row.estoque || 0),
      estoqueMin: 10,
    };
  }

  async buscarPorId(id) {
    if (!id) return null;
    const sql = `
      SELECT
        p.pro_id AS id,
        p.pro_nome AS nome,
        p.pro_descricao AS descricao,
        p.pro_preco_venda AS preco,
        p.pro_porcentagem_promocao AS desconto,
        c.cat_nome AS categoria,
        l.lab_nome AS marca
      FROM tb_Produtos p
      LEFT JOIN tb_Categorias c ON c.cat_id = p.pro_id_categoria
      LEFT JOIN tb_Laboratorios l ON l.lab_id = p.pro_id_laboratorio
      WHERE p.pro_id = ?
      LIMIT 1;
    `;

    const rows = await this.#db.ExecutaComando(sql, [id]);
    if (!rows.length) return null;
    return this.#mapRowToView(rows[0], 0);
  }

  async #buscarCategoriaIdPorNome(nome) {
    if (!nome) return null;
    const rows = await this.#db.ExecutaComando(
      "SELECT cat_id AS id FROM tb_Categorias WHERE cat_nome = ? LIMIT 1",
      [nome],
    );
    if (rows.length) return rows[0].id;
    const novoId = await this.#db.ExecutaComandoLastInserted(
      "INSERT INTO tb_Categorias (cat_nome) VALUES (?)",
      [nome],
    );
    return novoId;
  }

  async #buscarLaboratorioIdPorNome(nome) {
    if (!nome) return null;
    const rows = await this.#db.ExecutaComando(
      "SELECT lab_id AS id FROM tb_Laboratorios WHERE lab_nome = ? LIMIT 1",
      [nome],
    );
    if (rows.length) return rows[0].id;
    const novoId = await this.#db.ExecutaComandoLastInserted(
      "INSERT INTO tb_Laboratorios (lab_nome) VALUES (?)",
      [nome],
    );
    return novoId;
  }

  async criarProduto({ nome, descricao, preco, categoriaNome, marcaNome, descontoPercentual }) {
    const precoNumero = ProdutosModels.parseCurrencyToNumber(preco);
    const categoriaId = await this.#buscarCategoriaIdPorNome(categoriaNome);
    const laboratorioId = await this.#buscarLaboratorioIdPorNome(marcaNome);
    const descontoNum = Number(descontoPercentual || 0);

    const sql = `
      INSERT INTO tb_Produtos
        (pro_nome, pro_descricao, pro_preco_venda, pro_id_categoria, pro_id_laboratorio, pro_porcentagem_promocao)
      VALUES (?, ?, ?, ?, ?, ?);
    `;

    return this.#db.ExecutaComandoLastInserted(sql, [
      nome,
      descricao || null,
      precoNumero,
      categoriaId,
      laboratorioId,
      descontoNum,
    ]);
  }

  async deletarProduto(id) {
    if (!id) return false;
    return this.#db.ExecutaComandoNonQuery("DELETE FROM tb_Produtos WHERE pro_id = ?", [id]);
  }
}

module.exports = ProdutosModels;
