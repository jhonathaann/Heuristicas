import pyomo.environ as pyEnv
import time

def relax_and_fix(nome_arquivo, max_time):
    # lendo as instancias do arquivo
    with open(nome_arquivo, 'r') as file:

        referencia = file.readline().strip()
        n = int(file.readline().strip())
        valor_i = list(map(int, file.readline().strip().split()))
        
        bonus_ij = [[0] * n for _ in range(n)]
        for i in range(n - 1):
            linha = list(map(int, file.readline().strip().split()))
            for j, valor in enumerate(linha):
                bonus_ij[i][i + j + 1] = valor

        file.readline()
        tipo_restricao = int(file.readline().strip())
        capacidade = int(file.readline().strip())
        pesos_itens = list(map(int, file.readline().strip().split()))

    inicio_tempo = time.time()

    # inicializando as variaveis fixadas
    fixed_x = {}
    fixed_y = {}

    tamanho_bloco = max(1, n // 5)  # divide as variaveis em 5 blocos
    modelo = pyEnv.ConcreteModel()
    modelo.I = range(n)
    modelo.J = range(n)
    modelo.ab = [(i, j) for i in modelo.I for j in modelo.I if i < j]

    # criando as variaveis
    modelo.x = pyEnv.Var(modelo.I, within=pyEnv.Binary)
    modelo.y = pyEnv.Var(modelo.ab, within=pyEnv.Binary)

    # passando os valores lidos para o modelo
    modelo.p = pyEnv.Param(modelo.I, initialize=lambda modelo, i: pesos_itens[i]) # peso de cada item
    modelo.v = pyEnv.Param(modelo.I, initialize=lambda modelo, i: valor_i[i]) # valor de cada item
    modelo.b = pyEnv.Param(modelo.I, modelo.J, initialize=lambda modelo, i, j: bonus_ij[i][j]) # bonus do item i com o item j
    
    # ====== FUNCAO OBJETIVO

    soma_x = sum(modelo.v[i] * modelo.x[i] for i in modelo.I) # primeiro somatorio (pegando apenas o valor do item i que esta na solucao)

    soma_y = sum(modelo.b[i, j] * modelo.y[i, j] for i, j in modelo.ab)   # segundo somatorio (pegando o bonus do item i com o item j casos ambos estejam na solucao)

    modelo.objetivo = pyEnv.Objective(rule=(soma_x + soma_y), sense=pyEnv.maximize) # adicionando a funcao objetivo ao modelo

    # ====== RESTRICOES

    # restricao 1: os itens colocados na mochila devem ter um peso total <= capacidade da mochila
    def restricao_um(modelo, i):
        return sum(modelo.p[i] * modelo.x[i] for i in modelo.I) <= capacidade

    modelo.rest1 = pyEnv.Constraint(modelo.J, rule=restricao_um)

    # restricao 2: sistemas de equacoes que garante que o bonus so seja colocado na solucao quando ambos os itens estivem na solucao
    def restricao_dois(modelo, i, j):
        return modelo.y[i, j] <= modelo.x[i]
    modelo.rest2 = pyEnv.Constraint(modelo.ab, rule=restricao_dois)

    def restricao_tres(modelo, i, j):
        return modelo.y[i, j] <= modelo.x[j]
    modelo.rest3 = pyEnv.Constraint(modelo.ab, rule=restricao_tres)

    def restricao_quatro(modelo, i, j):
        return modelo.y[i, j] >= modelo.x[i] + modelo.x[j] - 1
    modelo.rest4 = pyEnv.Constraint(modelo.ab, rule=restricao_quatro)

    # relax-and-fix Iterativo (começa em 0, vai ate a quant de variaveis (n) com passo de: tamanho do bloco)
    for inicio in range(0, n, tamanho_bloco):
        end = min(inicio + tamanho_bloco, n)

        # fixando as variavies que ja foram resolvidas (na primeira iteracao ele nao ira fixar nenhuma)
        for i in fixed_x:
            modelo.x[i].fix(fixed_x[i])
        for (i, j) in fixed_y:
            modelo.y[i, j].fix(fixed_y[(i, j)])

        # faz relaxacao linear no bloco atual
        for i in range(inicio, end):
            modelo.x[i].unfix()
        for (i, j) in modelo.ab:
            # verificando se eu to em uma posicao valida dentro do bloco
            # valido = o meu inicio tem que estar antes da posicao atual (i ou j eh a posicao atual)
            if inicio <= i < end or inicio <= j < end:
                modelo.y[i, j].unfix()

        # resolve o subproblema
        solver = pyEnv.SolverFactory('glpk')
        resultado = solver.solve(modelo, tee=False)

        # registrando as solucoes fixadas
        for i in range(inicio, end):
            fixed_x[i] = round(pyEnv.value(modelo.x[i]))
        for (i, j) in modelo.ab:
            if inicio <= i < end or inicio <= j < end:
                fixed_y[(i, j)] = round(pyEnv.value(modelo.y[i, j]))

        # chegando o tempo
        if time.time() - inicio_tempo > max_time:
            print("Tempo limite atingido.")
            break

    resultado_funcao = pyEnv.value(modelo.objetivo)
    mochila = [fixed_x[i] for i in modelo.I]
    return resultado_funcao, mochila, n, pesos_itens

resultado_funcao, mochila, n, pesos_itens = relax_and_fix("C:/Users/jhona/OneDrive/Faculdade/LEXA/IC/Relax_and_Fix/teste.txt", max_time=60)

print("Valor da função objetivo:", resultado_funcao)
print("Itens que foram colocados na mochila:")

peso = 0
for i in range(n):
    print(f"Item {i}: {mochila[i]}")
    if mochila[i] == 1:
        peso += pesos_itens[i]

print("Peso total dos itens:", peso)
