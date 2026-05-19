const express = require('express');
const ComprasController = require('../controllers/comprasController');
const db = require('../models');

const router = express.Router();
const controller = new ComprasController();

router.get("/cadastrar-compra", async(req, res, next) =>{
    const userId = req.session.userId;
    if (!userId) {
        return res.redirect('/login');
    }

    const [pedido] = await db.query(
        `SELECT p.id, produtos.nome AS produto, p.quantidade, p.preco_total
        FROM pedidos_compra p
        JOIN pedido_itens pi ON p.id = pi.pedido_id
        JOIN produtos pr ON pi.produto_id = pr.id
        WHERE p.id = ?`, [userId]
    );

    res.render("receber-produto",{
        pedido: pedido[0]
    });
});

router.post("/receber", async(req, res) => {
    const {pedidoID, quantidadeRecebida, lote, validade} = req.body;

    const [pedido] = await db.query(`
        SELECT * FROM pedido_itens
        WHERE pedido_id = ?`, [pedidoID]
    );

    if (!pedido.length) {
        return res.send("Pedido não encontrado");
    }
    if(quantidadeRecebida !== pedido[0].quantidade){
        return res.send("Divergencia no pedido");
    }

    await db.query(`
        INSERT INTO estoque (produto_id, quantidade, lote, validade)
        VALUES (?, ?, ?, ?)`, [pedido[0].produto_id, quantidadeRecebida, lote, validade]
    );
    await db.query(`
        UPDATE pedidos_compra
        SET status = 'recebido'
        WHERE id = ?`, [pedidoID]
    );

    res.send("Produto recebido com sucesso");
}); 

module.exports = router;