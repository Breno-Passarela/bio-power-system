document.addEventListener("DOMContentLoaded", () => {
  const profile = document.getElementById("navbarProfile");
  const avatar = document.getElementById("profileAvatar");
  const loginText = document.getElementById("loginText");
  const profileDropdown = document.getElementById("profileDropdown");
  const logoutBtn = document.getElementById("logoutBtn");
  const token = localStorage.getItem("token");

  const hamburgerMenu = document.getElementById("hamburgerMenu");
  const mobileMenuOverlay = document.getElementById("mobileMenuOverlay");
  const closeMenuButton = document.getElementById("closeMenuButton");
  const mobileAuthLoggedOut = document.getElementById("mobileAuthLoggedOut");
  const mobileAuthLoggedIn = document.getElementById("mobileAuthLoggedIn");
  const mobileAvatar = document.getElementById("mobileAvatar");
  const mobileLogoutBtn = document.getElementById("mobileLogoutBtn");
  const mobileLoginButton = document.querySelector(".mobile-login-button");

  const searchIconMobile = document.getElementById("searchIconMobile");
  const searchInputMobile = document.getElementById("searchInputMobile");
  const navbarSearch = document.getElementById("navbarSearch");
  const searchCloseMobile = document.getElementById("searchCloseMobile");
  const searchSubmitMobile = document.getElementById("searchSubmitMobile");


  const navbar = document.querySelector(".navbar");

  if (token) {
    profileDropdown.style.display = "flex";
    avatar.src =
      "https://i.pravatar.cc/150?img=" + Math.floor(Math.random() * 70 + 1);
    avatar.style.display = "block";
    loginText.style.display = "none";
    profile.classList.add("logged-in");

    mobileAuthLoggedIn.style.display = "flex";
    mobileAuthLoggedOut.style.display = "none";
    mobileAvatar.src = avatar.src;
  } else {
    profileDropdown.style.display = "none";

    avatar.style.display = "none";
    loginText.style.display = "block";
    profile.onclick = () => {
      window.location.href = "./src/pages/auth-login.html";
    };

    mobileAuthLoggedIn.style.display = "none";
    mobileAuthLoggedOut.style.display = "block";
    mobileLoginButton.onclick = () => {
      window.location.href = "./src/pages/auth-login.html";
    };
  }

  logoutBtn.addEventListener("click", (e) => {
    e.preventDefault();
    localStorage.removeItem("token");
    window.location.href = "./src/pages/auth-login.html";
  });

  mobileLogoutBtn.addEventListener("click", (e) => {
    e.preventDefault();
    localStorage.removeItem("token");
    window.location.href = "./src/pages/auth-login.html";
  });

  hamburgerMenu.addEventListener("click", () => {
    mobileMenuOverlay.classList.add("active");
    document.body.style.overflow = "hidden";
  });

  closeMenuButton.addEventListener("click", () => {
    mobileMenuOverlay.classList.remove("active");
    document.body.style.overflow = "";
  });

  mobileMenuOverlay.addEventListener("click", (e) => {
    if (e.target === mobileMenuOverlay) {
      mobileMenuOverlay.classList.remove("active");
      document.body.style.overflow = "";
    }
  });

  const performSearch = () => {
    const searchTerm = searchInputMobile.value.trim();
    if (searchTerm) {
      console.log("Searching for:", searchTerm);
    }
    if (navbarSearch.classList.contains("search-active")) {
      closeMobileSearch();
    }
  };

  const closeMobileSearch = () => {
    navbarSearch.classList.remove("search-active");
    searchInputMobile.value = "";
  };

  searchIconMobile.addEventListener("click", () => {
    navbarSearch.classList.add("search-active");
    searchInputMobile.focus();
  });

  searchCloseMobile.addEventListener("click", closeMobileSearch);

  searchSubmitMobile.addEventListener("click", performSearch);

  searchInputMobile.addEventListener("keypress", (e) => {
    if (e.key === "Enter") {
      e.preventDefault();
      performSearch();
    }
  });

  document.addEventListener("click", (e) => {
    if (
      !navbarSearch.contains(e.target) &&
      navbarSearch.classList.contains("search-active")
    ) {
      closeMobileSearch();
    }
  });

  navbarSearch.addEventListener("click", (e) => {
    e.stopPropagation();
  });

  window.addEventListener("scroll", () => {
    if (window.scrollY > 0) { 
      navbar.classList.add("scrolled");
    } else { 
      navbar.classList.remove("scrolled");
    }
  });
});