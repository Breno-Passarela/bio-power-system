const express = require('express');
const RegisterController = require('../controllers/registerController');

const router = express.Router();
const controller = new RegisterController();

router.get("/", controller.register);
/* router.post("/register-user", controller.registerUser); */

module.exports = router;

