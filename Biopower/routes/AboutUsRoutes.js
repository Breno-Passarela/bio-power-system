const express = require('express');
const AboutUsController = require("../controllers/aboutUsController");

const router = express.Router();
const controller = new AboutUsController();

router.get("/", controller.aboutUs);

module.exports = router;