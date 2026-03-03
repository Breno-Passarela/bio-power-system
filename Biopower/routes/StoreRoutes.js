const express = require('express');
const StoreController = require('../controllers/storeController');

const router = express.Router();
const controller = new StoreController();

router.get("/", controller.store);

module.exports = router;    