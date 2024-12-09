import random

# fase da construçao da solução inicial, de forma golusa e aleatorizada
def construcao_gulosa_randomizada(itens, valor_i, peso_i, capacidade, alpha):
    # inicializando a solucao e a capacidade da mochila
    solucao = []
    capacidade_usada = 0

    # enquanto ainda houver itens para processar
    while len(itens) > 0:
        # atualizar a RCL com base em valor/peso e na função alpha
        RCL = gerar_RCL(itens, valor_i, peso_i, capacidade, capacidade_usada, alpha)

        # se a lista de candidatos estiver vazia, não há mais itens válidos para adicionar
        if len(RCL) == 0:
            break

        # escolhendo um item aleatoriamente da RCL
        item = random.choice(RCL)

        # adiciona o item à solução, sem necessidade de verificar o peso novamente
        solucao.append(item)
        capacidade_usada += peso_i[item]
        
        # removendo o item selecionado da lista de itens
        itens.remove(item)
    
    return solucao, capacidade_usada

# função que cria a lista restrita de candidatos com o uso de alpha
def gerar_RCL(itens, valor, peso, capacidade, capacidade_usada, alpha):
    RCL = []
    razoes = []

    # calcular a razão valor/peso para todos os itens que cabem na mochila
    for item in itens:
        if peso[item] + capacidade_usada <= capacidade:
            razao = valor[item] / peso[item]
            razoes.append(razao)

    # se não houver razões (nenhum item cabe), retornar RCL vazia
    if not razoes:
        return []

    # definir o limite superior para a RCL com base no valor máximo de razão e alpha
    max_razao = max(razoes)
    limite = max_razao * alpha

    # construir a RCL incluindo apenas itens cuja razão esteja dentro do limite
    for item in itens:
        if peso[item] + capacidade_usada <= capacidade and (valor[item] / peso[item]) >= limite:
            RCL.append(item)
        
    return RCL

# função que faz a busca local, em busca de melhorias
def busca_local(solucao, itens, valor_i, peso_i, par_itens, bonus_par, capacidade, capacidade_usada):
    melhorou = True
    while melhorou:
        melhorou = False
        
        for item in itens:
            nova_solucao = tenta_trocar_ou_adicionar(item, solucao, valor_i, peso_i, par_itens, bonus_par, capacidade, capacidade_usada)
            valor_atual_solucao = avaliar_solucao(solucao, valor_i, par_itens, bonus_par)
            novo_valor_solucao = avaliar_solucao(nova_solucao, valor_i, par_itens, bonus_par)

            if novo_valor_solucao > valor_atual_solucao:
                solucao = nova_solucao
                melhorou = True

    return solucao

# função que tenta realizar algumas mudanças na solucao
def tenta_trocar_ou_adicionar(item, solucao, valor_i, peso_i, par_itens, bonus_par, capacidade, capacidade_usada):
    nova_solucao = solucao.copy()

    # tentar adicionar o item se a capacidade permitir
    if peso_i[item] + capacidade_usada <= capacidade:
        solucao.append(item)
        capacidade_usada += peso_i[item]
    
    # tentar trocar os itens da solução
    for i in range(len(solucao)):
        item_trocado = solucao[i]
        nova_solucao[i] = item
        nova_capacidade_usada = capacidade_usada - peso_i[item_trocado] + peso_i[item]

        valor_da_solucao_original = sum(valor_i[i] for i in solucao)
        valor_da_nova_solucao = sum(valor_i[i] for i in nova_solucao)

        if nova_capacidade_usada <= capacidade and valor_da_nova_solucao > valor_da_solucao_original:
            return nova_solucao

    return solucao

# função para avaliar a solucao
def avaliar_solucao(solucao, valor_i, par_itens, bonus_par):
    valor = sum(valor_i[i] for i in solucao)

    for (a, b) in par_itens:
        if a in solucao and b in solucao:
            valor += bonus_par[(a, b)]

    return valor

def GRASP(itens, valores, pesos, par_itens, bonus_pares, capacidade, max_iteracoes, alpha):
    melhor_solucao = None
    melhor_valor = 0

    for i in range(max_iteracoes):
        # fase da construcao da solucao
        solucao, capacidade_usada = construcao_gulosa_randomizada(itens.copy(), valores, pesos, capacidade, alpha)

        # fase da busca local
        solucao = busca_local(solucao, itens, valores, pesos, par_itens, bonus_pares, capacidade, capacidade_usada)

        # avaliando a solucao
        valor_solucao = avaliar_solucao(solucao, valores, par_itens, bonus_pares)

        # atualiza a melhor solucao
        if valor_solucao > melhor_valor:
            melhor_solucao = solucao
            melhor_valor = valor_solucao

    return melhor_solucao, melhor_valor

# exemplo de uso
itens = [0, 1, 2, 3, 4]
valores = [10, 20, 30, 40, 70]
pesos = [2, 8, 13, 10, 30]
par_itens = [(0, 1), (2, 3)]
bonus_pares = {(0, 1): 10, (2, 3): 150}
capacidade = 40
max_iteracoes = 100000
alpha = 0.5  # você pode ajustar esse valor conforme necessário

melhor_solucao, melhor_valor = GRASP(itens, valores, pesos, par_itens, bonus_pares, capacidade, max_iteracoes, alpha)
print(f"Melhor solução encontrada: {melhor_solucao}")
print(f"Melhor valor da solução encontrada: {melhor_valor}")
