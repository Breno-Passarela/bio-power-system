const express = require('express');
const StoreController = require('../controllers/storeController');

const router = express.Router();
const controller = new StoreController();

router.get("/", (req, res, next) => {
	Promise.resolve(controller.store(req, res)).catch(next);
});

module.exports = router;