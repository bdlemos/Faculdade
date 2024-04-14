import networkx as nx
import matplotlib.pyplot as plt

def plot_graph(graph, node_colors):
    pos = nx.spring_layout(graph)  # Define a posição dos nós no gráfico
    nx.draw(graph, pos, with_labels=True, node_color=node_colors, node_size=700, cmap=plt.cm.rainbow)  # Plota o grafo com cores nos nós
    plt.show()

def main():
    # Lê as entradas do grafo
    graph_input = []
    colors = {}
    graph = nx.Graph()
    with open('inA-Coloracao.txt', 'r') as file:
        for line in file:
            parts = line.split()
            if parts[0] == 'n':
                num_nodes = int(parts[1])
                for node in range(1, num_nodes + 1):
                    graph.add_node(node)
            elif parts[0] == 'e':
                node1 = int(parts[1])
                node2 = int(parts[2])
                graph.add_edge(node1, node2)

    colors_input = {
        7: 1,
        2: 4,
        5: 4,
        3: 5,
        6: 5,
        11: 7,
        9: 8,
        1: 10,
        10: 10,
        4: 11,
        8: 11,
    }

    for node, color in colors_input.items():
        print(f"{node} {color}")

    # Plota o grafo
    plot_graph(graph, [colors_input[node] for node in graph.nodes()])

if __name__ == "__main__":
    main()
