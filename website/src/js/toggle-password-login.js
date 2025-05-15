function passwordShow(toggleId, inputId) {
    const toggleIcon = document.getElementById(toggleId);
    const input = document.getElementById(inputId);
    
    const isPassword = input.type === "password";
    input.type = isPassword ? "text" : "password";
    toggleIcon.classList.toggle("fa-eye");
    toggleIcon.classList.toggle("fa-eye-slash");
}