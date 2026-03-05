const products = require("../data/products");

class AdminController {
  dashboard(req, res) {
    res.render("admin/dashboard", {
      layout: false,
      user: req.session.user,
      products,
      flash: req.query.flash || null,
    });
  }

  addProduct(req, res) {
    const {
      nome,
      preco,
      desconto,
      credito,
      imagem,
      alt,
      categoria,
      marca,
      sabor,
      estoque,
      estoqueMin,
    } = req.body;
    if (nome && preco) {
      products.push({
        nome,
        preco,
        desconto: desconto || "no boleto ou pix",
        credito: credito || "",
        imagem: req.file
          ? "/assets/imgs/product/" + req.file.filename
          : imagem || "/assets/imgs/product/default.png",
        alt: alt || nome,
        categoria: categoria || "Outros",
        marca: marca || "",
        sabor: sabor || "Sem sabor",
        estoque: parseInt(estoque) || 0,
        estoqueMin: parseInt(estoqueMin) > 0 ? parseInt(estoqueMin) : 10,
      });
    }
    res.redirect("/admin/dashboard?flash=produto-adicionado#products");
  }

  updateStock(req, res) {
    const index = parseInt(req.params.index, 10);
    const quantidade = parseInt(req.body.quantidade, 10);
    if (
      !isNaN(index) &&
      index >= 0 &&
      index < products.length &&
      !isNaN(quantidade)
    ) {
      products[index].estoque = Math.max(
        0,
        (products[index].estoque || 0) + quantidade,
      );
    }
    res.redirect("/admin/dashboard?flash=estoque-atualizado#stock");
  }

  deleteProduct(req, res) {
    const index = parseInt(req.params.index, 10);
    if (!isNaN(index) && index >= 0 && index < products.length) {
      products.splice(index, 1);
    }
    res.redirect("/admin/dashboard#products");
  }
}

module.exports = AdminController;
