const products = require("../data/products");

class storeController {
  store(req, res) {
    res.render("store", { products });
  }
}

module.exports = storeController;
