const USERS = [
  {
    email: "admin@biopower.com",
    password: "admin123",
    role: "admin",
    name: "Administrador",
  },
  {
    email: "cliente@biopower.com",
    password: "cliente123",
    role: "client",
    name: "Cliente Premium",
  },
];

class AutentificacaoController {
  autentificacao(req, res) {
    res.render("autentificacao", { layout: false });
  }

  login(req, res) {
    res.render("login", {
      layout: false,
      error: null,
      form: { email: "" },
    });
  }

  loginPost(req, res) {
    const email = (req.body.email || "").trim().toLowerCase();
    const password = (req.body.password || "").trim();
    const user = USERS.find(
      (entry) => entry.email === email && entry.password === password,
    );

    if (!user) {
      return res.render("login", {
        layout: false,
        error: "Credenciais inválidas. Tente novamente.",
        form: { email },
      });
    }

    req.session.user = {
      email: user.email,
      role: user.role,
      name: user.name,
    };

    const redirectTo = user.role === "admin" ? "/admin/dashboard" : "/";
    return res.redirect(redirectTo);
  }

  logout(req, res) {
    req.session.destroy(() => {
      res.redirect("/auth");
    });
  }

  register(req, res) {
    res.render("register", { layout: false });
  }
}

module.exports = AutentificacaoController;
