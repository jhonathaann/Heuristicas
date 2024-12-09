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

    start_time = time.time()

    # Inicializando variáveis fixadas
    fixed_x = {}
    fixed_y = {}

    bloco_tamanho = max(1, n // 5)  # Divide as variáveis em 5 blocos (ajustável)
    modelo = pyEnv.ConcreteModel()
    modelo.I = range(n)
    modelo.J = range(n)
    modelo.ab = [(i, j) for i in modelo.I for j in modelo.I if i < j]

    # Criando variáveis binárias
    modelo.x = pyEnv.Var(modelo.I, within=pyEnv.Binary)
    modelo.y = pyEnv.Var(modelo.ab, within=pyEnv.Binary)

    modelo.p = pyEnv.Param(modelo.I, initialize=lambda modelo, i: pesos_itens[i])
    modelo.v = pyEnv.Param(modelo.I, initialize=lambda modelo, i: valor_i[i])
    modelo.b = pyEnv.Param(modelo.I, modelo.J, initialize=lambda modelo, i, j: bonus_ij[i][j])

    soma_x = sum(modelo.v[i] * modelo.x[i] for i in modelo.I)
    soma_y = sum(modelo.b[i, j] * modelo.y[i, j] for i, j in modelo.ab)
    modelo.objetivo = pyEnv.Objective(rule=(soma_x + soma_y), sense=pyEnv.maximize)

    def restricao_um(modelo, i):
        return sum(modelo.p[i] * modelo.x[i] for i in modelo.I) <= capacidade

    modelo.rest1 = pyEnv.Constraint(modelo.J, rule=restricao_um)

    def restricao_dois(modelo, i, j):
        return modelo.y[i, j] <= modelo.x[i]

    modelo.rest2 = pyEnv.Constraint(modelo.ab, rule=restricao_dois)

    def restricao_tres(modelo, i, j):
        return modelo.y[i, j] <= modelo.x[j]

    modelo.rest3 = pyEnv.Constraint(modelo.ab, rule=restricao_tres)

    def restricao_quatro(modelo, i, j):
        return modelo.y[i, j] >= modelo.x[i] + modelo.x[j] - 1

    modelo.rest4 = pyEnv.Constraint(modelo.ab, rule=restricao_quatro)

    # Relax-and-Fix Iterativo
    for start in range(0, n, bloco_tamanho):
        end = min(start + bloco_tamanho, n)

        # Fixar variáveis previamente resolvidas
        for i in fixed_x:
            modelo.x[i].fix(fixed_x[i])
        for (i, j) in fixed_y:
            modelo.y[i, j].fix(fixed_y[(i, j)])

        # Relaxar o bloco atual
        for i in range(start, end):
            modelo.x[i].unfix()
        for (i, j) in modelo.ab:
            if start <= i < end or start <= j < end:
                modelo.y[i, j].unfix()

        # Resolver o subproblema
        solver = pyEnv.SolverFactory('glpk')
        resultado = solver.solve(modelo, tee=False)

        # Registrar soluções fixadas
        for i in range(start, end):
            fixed_x[i] = round(pyEnv.value(modelo.x[i]))
        for (i, j) in modelo.ab:
            if start <= i < end or start <= j < end:
                fixed_y[(i, j)] = round(pyEnv.value(modelo.y[i, j]))

        # Checar limite de tempo
        if time.time() - start_time > max_time:
            print("Tempo limite atingido.")
            break

    # Retornar resultados
    resultado_funcao = pyEnv.value(modelo.objetivo)
    mochila = [fixed_x[i] for i in modelo.I]
    return resultado_funcao, mochila, n, pesos_itens

# Uso da função
resultado_funcao, mochila, n, pesos_itens = relax_and_fix("C:/Users/jhona/OneDrive/Faculdade/LEXA/IC/Relax_and_Fix/teste.txt", max_time=60)

print("Valor da função objetivo:", resultado_funcao)
print("Itens que foram colocados na mochila:")

peso = 0
for i in range(n):
    print(f"Item {i}: {mochila[i]}")
    if mochila[i] == 1:
        peso += pesos_itens[i]

print("Peso total dos itens:", peso)
