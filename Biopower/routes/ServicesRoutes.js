const express = require("express");
const ServicesController = require("../controllers/ServicesController");

const router = express.Router();
const controller = new ServicesController();

router.get("/services", (req, res, next) =>
  Promise.resolve(controller.page(req, res)).catch(next),
);

router.post("/services/hire", (req, res, next) =>
  Promise.resolve(controller.contratar(req, res)).catch(next),
);

module.exports = router;
