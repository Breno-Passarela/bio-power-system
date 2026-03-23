const express = require("express");
const PagesController = require("../controllers/PagesController");

const router = express.Router();
const controller = new PagesController();

router.get("/shopping-cart", controller.shoppingCart.bind(controller));
router.get("/product-buy", controller.productBuy.bind(controller));
router.get("/product/:index", controller.productBuy.bind(controller));
router.get("/product-list", controller.productList.bind(controller));
router.get("/forms-product", controller.insertProduct.bind(controller));
router.get("/list-product", controller.listProduct.bind(controller));
router.get("/forgot-password", controller.forgotPassword.bind(controller));
router.get("/sending-email", controller.sendingEmail.bind(controller));
router.get("/password-reset", controller.passwordReset.bind(controller));
router.get("/password-reset-success", controller.passwordResetSuccess.bind(controller));

module.exports = router;
