const express = require("express");
const AutentificacaoController = require("../controllers/AutentificacaoController");

const router = express.Router();
const controller = new AutentificacaoController();

router.get("/auth", controller.autentificacao);
router.get("/login", controller.login);
router.post("/login", controller.loginPost);
router.get("/logout", controller.logout);
router.get("/register", controller.register);

module.exports = router;
