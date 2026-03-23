const products = require("../data/products");

class PagesController {
  shoppingCart(req, res) {
    res.render("shoppingCart", { layout: true });
  }

  productBuy(req, res) {
    const index = Number(req.params.index ?? req.query.index);
    const product = !Number.isNaN(index) && products[index] ? products[index] : null;
    res.render("productBuy", { layout: false, product });
  }

  productList(req, res) {
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
