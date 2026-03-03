const express = require('express');
const HomeController = require('../controllers/homeController');

const router = express.Router();
const controller = new HomeController();
router.get("/", controller.home);

module.exports = router;