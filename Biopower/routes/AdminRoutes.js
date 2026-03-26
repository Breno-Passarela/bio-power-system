const express = require("express");
const path = require("path");
const multer = require("multer");
const AdminController = require("../controllers/AdminController");

const router = express.Router();
const controller = new AdminController();

const storage = multer.diskStorage({
  destination: path.join(__dirname, "../public/assets/imgs/product"),
  filename(req, file, cb) {
    const ext = path.extname(file.originalname);
    cb(null, Date.now() + ext);
  },
});
const upload = multer({
  storage,
  limits: { fileSize: 5 * 1024 * 1024 }, // 5 MB
  fileFilter(req, file, cb) {
    if (/image\/(jpeg|png|webp|gif)/.test(file.mimetype)) cb(null, true);
    else cb(new Error("Apenas imagens JPEG, PNG, WEBP ou GIF são permitidas."));
  },
});

function ensureAdmin(req, res, next) {
  if (req.session.user && (req.session.user.role === "admin" || req.session.user.role === "staff")) {
    return next();
  }
  return res.redirect("/login");
}

router.get("/", ensureAdmin, (req, res, next) => {
  Promise.resolve(controller.dashboard(req, res)).catch(next);
});
// rota legado para /dashboard/dashboard
router.get("/dashboard", ensureAdmin, (req, res) => res.redirect("/dashboard"));
router.post("/products", ensureAdmin, upload.single("imagem"), (req, res, next) =>
  Promise.resolve(controller.addProduct(req, res)).catch(next),
);
router.post("/products/delete/:id", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.deleteProduct(req, res)).catch(next),
);
router.post("/stock/update/:id", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.updateStock(req, res)).catch(next),
);

router.get("/services", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.listServices(req, res)).catch(next),
);
router.post("/services", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.createService(req, res)).catch(next),
);
router.put("/services/:id", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.updateService(req, res)).catch(next),
);
router.delete("/services/:id", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.deleteService(req, res)).catch(next),
);

router.get("/services/contratos", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.listContractedServices(req, res)).catch(next),
);
router.put("/services/contratos/:id/status", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.updateContractedServiceStatus(req, res)).catch(next),
);

// Usuarios (admin)
router.post("/users", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.createUser(req, res)).catch(next),
);
router.put("/users/:id", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.updateUser(req, res)).catch(next),
);
router.delete("/users/:id", ensureAdmin, (req, res, next) =>
  Promise.resolve(controller.deleteUser(req, res)).catch(next),
);

module.exports = router;
