(function() {
  const sections = document.querySelectorAll('.adm-section');
  const navItems = document.querySelectorAll('.adm-nav-item');
  const breadcrumb = document.getElementById('breadcrumbCurrent');

  function activateSection(id) {
    sections.forEach((s) => s.classList.remove('adm-section--active'));
    navItems.forEach((n) => n.classList.remove('adm-nav-item--active'));
    const target = document.getElementById(id);
    if (target) target.classList.add('adm-section--active');
    const navTarget = document.querySelector('[data-section="' + id + '"]');
    if (navTarget) {
      navTarget.classList.add('adm-nav-item--active');
      const label = navTarget.querySelector('span');
      if (breadcrumb && label) breadcrumb.textContent = label.textContent;
    }
    window.scrollTo({ top: 0, behavior: 'smooth' });
    closeSidebar();
  }

  navItems.forEach((item) => {
    item.addEventListener('click', (e) => {
      e.preventDefault();
      activateSection(item.dataset.section);
    });
  });

  document.querySelectorAll('[data-goto]').forEach((btn) => {
    btn.addEventListener('click', () => activateSection(btn.dataset.goto));
  });

  document.querySelectorAll('.adm-tab').forEach((tab) => {
    tab.addEventListener('click', () => {
      tab
        .closest('.adm-status-tabs')
        .querySelectorAll('.adm-tab')
        .forEach((t) => t.classList.remove('adm-tab--active'));
      tab.classList.add('adm-tab--active');
    });
  });

  // Notifications
  const notifBtn   = document.getElementById('notifBtn');
  const notifPanel = document.getElementById('notifPanel');
  const notifCount = document.getElementById('notifCount');
  const notifList  = document.getElementById('notifList');
  const notifEmpty = document.getElementById('notifEmpty');

  function updateCount() {
    if (!notifList || !notifCount || !notifEmpty) return;
    const n = notifList.querySelectorAll('.adm-notif-item--unread').length;
    notifCount.textContent = n;
    if (n === 0) notifCount.setAttribute('data-zero',''); else notifCount.removeAttribute('data-zero');
    if (notifList.children.length === 0) { notifEmpty.style.display = 'block'; } else { notifEmpty.style.display = 'none'; }
  }

  function markRead(item) {
    item.classList.remove('adm-notif-item--unread');
    const readBtn = item.querySelector('.adm-notif-item-read');
    if (readBtn) readBtn.style.opacity = '0';
    updateCount();
  }

  if (notifBtn && notifPanel && notifList) {
    notifBtn.addEventListener('click', function(e) {
      e.stopPropagation();
      const open = !notifPanel.hidden;
      notifPanel.hidden = open;
      notifBtn.setAttribute('aria-expanded', String(!open));
    });

    document.addEventListener('click', function(e) {
      if (!notifPanel.hidden && !document.getElementById('notifWrap').contains(e.target)) {
        notifPanel.hidden = true;
        notifBtn.setAttribute('aria-expanded', 'false');
      }
    });

    notifList.addEventListener('click', function(e) {
      const readBtn = e.target.closest('.adm-notif-item-read');
      if (readBtn) { e.stopPropagation(); markRead(readBtn.closest('.adm-notif-item')); return; }
    });

    const notifMarkAll = document.getElementById('notifMarkAll');
    if (notifMarkAll) {
      notifMarkAll.addEventListener('click', function() {
        notifList.querySelectorAll('.adm-notif-item--unread').forEach(markRead);
      });
    }

    updateCount();
  }

  // Sidebar
  const sidebar = document.getElementById('admSidebar');
  const overlay = document.getElementById('admOverlay');
  const hamburger = document.getElementById('admHamburger');

  function closeSidebar() {
    if (!sidebar || !overlay) return;
    sidebar.classList.remove('adm-sidebar--open');
    overlay.classList.remove('adm-overlay--visible');
  }

  if (hamburger && sidebar && overlay) {
    hamburger.addEventListener('click', () => {
      sidebar.classList.toggle('adm-sidebar--open');
      overlay.classList.toggle('adm-overlay--visible');
    });
    overlay.addEventListener('click', closeSidebar);
  }

  // Preview da imagem no formulário de novo produto
  function previewImagem(input) {
    const img = document.getElementById('previewImgProduto');
    if (!img) return;
    if (input.files && input.files[0]) {
      img.src = URL.createObjectURL(input.files[0]);
      img.style.display = 'block';
    } else {
      img.src = '';
      img.style.display = 'none';
    }
  }

  // SweetAlert2 — reposição de estoque
  function reporEstoque(btn) {
    const index = btn.dataset.index;
    const nome  = btn.dataset.nome || 'este produto';
    Swal.fire({
      title: 'Atualizar estoque',
      html: 'Produto: <strong>' + nome + '</strong><br>Informe a quantidade a <b>adicionar</b> (use número negativo para subtrair).',
      input: 'number',
      inputLabel: 'Quantidade',
      inputPlaceholder: 'Ex: 50',
      inputAttributes: { min: '-9999', step: '1' },
      showCancelButton: true,
      confirmButtonText: '<i class="fa-solid fa-boxes-stacked"></i> Atualizar',
      cancelButtonText: 'Cancelar',
      confirmButtonColor: '#cc0000',
      cancelButtonColor: '#6b7280',
      reverseButtons: true,
      inputValidator: function(value) {
        if (!value || isNaN(Number(value))) return 'Informe uma quantidade válida.';
      }
    }).then(function(result) {
      if (result.isConfirmed) {
        var form = document.getElementById('formRepor');
        if (!form) return;
        form.action = '/admin/stock/update/' + index;
        document.getElementById('reporQtd').value = result.value;
        form.submit();
      }
    });
  }

  // SweetAlert2 — exclusão de produtos reais (POST form)
  document.querySelectorAll('.form-delete-product').forEach(function(form) {
    form.addEventListener('submit', function(e) {
      e.preventDefault();
      const nome = form.dataset.nome || 'este produto';
      Swal.fire({
        title: 'Excluir produto?',
        html: 'Você está prestes a excluir <strong>' + nome + '</strong>.<br>Essa ação é irreversível.',
        icon: 'warning',
        showCancelButton: true,
        confirmButtonText: '<i class="fa-solid fa-trash"></i> Excluir',
        cancelButtonText: 'Cancelar',
        confirmButtonColor: '#cc0000',
        cancelButtonColor: '#6b7280',
        reverseButtons: true,
        focusCancel: true,
      }).then(function(result) {
        if (result.isConfirmed) form.submit();
      });
    });
  });

  // SweetAlert2 — ações de exclusão estática (outras seções)
  function confirmDelete(btn) {
    const row = btn.closest('tr') || btn.closest('.adm-card');
    Swal.fire({
      title: 'Confirmar exclusão',
      text: 'Essa ação é irreversível. Deseja realmente continuar?',
      icon: 'warning',
      showCancelButton: true,
      confirmButtonText: '<i class="fa-solid fa-trash"></i> Excluir',
      cancelButtonText: 'Cancelar',
      confirmButtonColor: '#cc0000',
      cancelButtonColor: '#6b7280',
      reverseButtons: true,
      focusCancel: true,
    }).then(function(result) {
      if (result.isConfirmed && row) row.remove();
    });
  }

  window.activateSection = activateSection;
  window.previewImagem = previewImagem;
  window.reporEstoque = reporEstoque;
  window.confirmDelete = confirmDelete;
})();
