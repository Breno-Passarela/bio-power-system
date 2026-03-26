const ProdutosModels = require("../models/produtosModels");

const produtosModel = new ProdutosModels();

class PagesController {
  shoppingCart(req, res) {
    res.render("shoppingCart", { layout: true });
  }

  async productBuy(req, res) {
    const index = Number(req.params.index ?? req.query.index);
    let product = null;

    try {
      if (!Number.isNaN(index)) {
        product = await produtosModel.buscarPorId(index);
        if (!product) {
          const lista = await produtosModel.listarParaInterface();
          product = lista[index] || null;
        }
      }
    } catch (err) {
      console.error("Erro ao carregar produto:", err);
      product = null;
    }

    if (!product) {
      return res.redirect("/product-list");
    }

    res.render("productBuy", { layout: false, product });
  }

  async productList(req, res) {
    let products = [];
    try {
      products = await produtosModel.listarParaInterface();
    } catch (err) {
      console.error("Erro ao listar produtos:", err);
      products = [];
    }

    res.render("store", { products });
  }

  insertProduct(req, res) {
    res.render("insertProduct", { layout: false });
  }

  listProduct(req, res) {
    res.render("listProduct", { layout: false });
  }

  forgotPassword(req, res) {
    res.render("forgot", { layout: false });
  }

  sendingEmail(req, res) {
    res.render("sendingEmail", { layout: false });
  }

  passwordReset(req, res) {
    res.render("passwordReset", { layout: false });
  }

  passwordResetSuccess(req, res) {
    res.render("passwordResetSuccess", { layout: false });
  }
}

module.exports = PagesController;
