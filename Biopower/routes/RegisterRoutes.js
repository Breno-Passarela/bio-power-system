const express = require('express');
const RegisterController = require('../controllers/registerController');

const router = express.Router();
const controller = new RegisterController();

router.get("/", controller.register);

module.exports = router;

