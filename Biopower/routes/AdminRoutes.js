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

router.get("/", ensureAdmin, controller.dashboard);
// rota legado para /dashboard/dashboard
router.get("/dashboard", ensureAdmin, (req, res) => res.redirect("/dashboard"));
router.post("/products", ensureAdmin, upload.single("imagem"), (req, res) =>
  controller.addProduct(req, res),
);
router.post("/products/delete/:index", ensureAdmin, (req, res) =>
  controller.deleteProduct(req, res),
);
router.post("/stock/update/:index", ensureAdmin, (req, res) =>
  controller.updateStock(req, res),
);

module.exports = router;
