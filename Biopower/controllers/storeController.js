const ProdutosModels = require("../models/produtosModels");

const produtosModel = new ProdutosModels();

class storeController {
  async store(req, res) {
    let products = [];
    try {
      products = await produtosModel.listarParaInterface();
    } catch (err) {
      console.error("Erro ao listar produtos da loja:", err);
      products = [];
    }

    res.render("store", { products });
  }
}

module.exports = storeController;
