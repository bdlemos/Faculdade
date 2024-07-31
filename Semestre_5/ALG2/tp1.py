# TRABALHO PRATICO 1 - TRIANGULACAO DE POLIGONOS
import numpy as np
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from matplotlib.patches import Polygon
import matplotlib.pyplot as plt

import sys

def read_polygon(file):
    vertices = []
    with open(file, 'r') as f:
        content = f.read().split(' ')
        for v in content[1:]:
            v = v.split('/')
            vertices += [float(v[0])/int(v[1])] if len(v) > 1 else []

    return np.array([vertices[i:i+2] for i in range(0, len(vertices), 2)])

def plot_polygon(polygon, triangles, frames):
    fig = make_subplots(rows=1, cols=2, subplot_titles=("Polygon", "Current Triangle"))


    # Set up the frames for animation
    for i, frame in enumerate(frames):
        fig.add_trace(go.Scatter(x=frame[0], y=frame[1], mode="lines+markers", name=f"Iteraçao - {i+1}", 
                                 marker=dict(color="blue"), line=dict(color="black", width=0.3)), row=1, col=1)
        x = [x for x, _ in triangles[i]]
        y = [y for _, y in triangles[i]]
        fig.add_trace(go.Scatter(x=x,
                      y=y,mode="lines+markers", name=f"Triangulo - {i+1}",
                      marker=dict(color="blue"), line=dict(color="black", width=0.3)), row=1, col=2)

    # Slider
    steps = []
    for i in range(0,len(fig.data),2):
        step = dict(
            method="update",
            args=[{"visible": [False] * len(fig.data)},
                  {"title": f"Frame {(i)/2}"}],
        )

        # Update the visible traces
        # Only the last in plot 1 and all traces in plot 2
        step["args"][0]["visible"][i] = True
        for j in range(1,i+2,2):
            step["args"][0]["visible"][j] = True
        steps.append(step)


    # Add layout with buttons and sliders
    fig.update_layout(
        title_text="Triangulaçao de Poligonos",
        xaxis1=dict(range=[min(polygon[:, 0]) - 5, max(polygon[:, 0]) + 5]),
        yaxis1=dict(range=[min(polygon[:, 1]) - 5, max(polygon[:, 1]) + 5]),
        xaxis2=dict(range=[min(polygon[:, 0]) - 5, max(polygon[:, 0]) + 5]),
        yaxis2=dict(range=[min(polygon[:, 1]) - 5, max(polygon[:, 1]) + 5]),
        updatemenus=[{
            "buttons": [
                {
                    "args": [None, {"frame": {"duration": 300, "redraw": False}, "fromcurrent": True, "transition": {"duration": 5}}],
                    "label": "Play",
                    "method": "animate"
                },
                {
                    "args": [[None], {"frame": {"duration": 0, "redraw": False}, "mode": "immediate", "transition": {"duration": 0}}],
                    "label": "Pause",
                    "method": "animate"
                },
                {
                    "args": [None, {"frame": {"duration": 300, "redraw": False}, "fromcurrent": True, "direction": "reverse", "transition": {"duration": 5}}],
                    "label": "Retrocede",
                    "method": "animate"
                },
                {
                    "args": [{"visible": [True, True]}],  # Both traces will be visible
                    "label": "Show All",
                    "method": "update"
                }
            ],
            "direction": "left",
            "pad": {"r": 10, "t": 87},
            "showactive": True,
            "type": "buttons",
            "x": 0.1,
            "xanchor": "right",
            "y": 0,
            "yanchor": "top"
        }],
        sliders=[{
            "active": 0,
            "yanchor": "top",
            "xanchor": "left",
            "currentvalue": {
                "font": {"size": 20},
                "prefix": "Frame:",
                "visible": True,
                "xanchor": "right"
            },
            "transition": {"duration": 300, "easing": "cubic-in-out"},
            "pad": {"b": 10, "t": 50},
            "len": 0.9,
            "x": 0.1,
            "y": 0,
            "steps": steps
        }]
    )

    # Show the figure
    fig.show()

def ear_clipping(polygon):
    def is_point_inside_triangle(p, p0, p1, p2):
        def sign(p1, p2, p3):
            return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1])
        b1 = sign(p, p0, p1) <= 0.0
        b2 = sign(p, p1, p2) <= 0.0
        b3 = sign(p, p2, p0) <= 0.0
        return ((b1 == b2) and (b2 == b3))
    
    def is_ear(polygon, i):
        p0 = polygon[i-1]
        p1 = polygon[i]
        p2 = polygon[(i+1)%len(polygon)]
        for j in range(len(polygon)):
            if j == i or j == i-1:
                continue
            if is_point_inside_triangle(polygon[j], p0, p1, p2):
                return False
        return True
    
    def remove_ear(polygon, i):
        return np.delete(polygon, i, axis=0)
    

    triangles = []
    frames = []
    while(len(polygon) > 3):
        #print(polygon)
        for i in range(len(polygon)):
            if is_ear(polygon, i):
                triangles.append([polygon[i-1], polygon[i], polygon[(i+1)%len(polygon)], polygon[i-1]])
                points_x = [x for x, y in triangles[-1]]
                points_y = [y for x, y in triangles[-1]]
                frames += [(polygon[:,0], polygon[:,1])]
                polygon = remove_ear(polygon, i)
                break
    

    return triangles,frames


def plot_triangles(triangles, ax):
    for triangle in triangles:
        ax.plot([triangle[0][0], triangle[1][0], triangle[2][0], triangle[0][0]],
            [triangle[0][1], triangle[1][1], triangle[2][1], triangle[0][1]],
            color='b', linestyle='-', linewidth=0.4)


if __name__ == "__main__":
    for name in sys.argv[1:]:
        polygon = read_polygon(name)
        polygon = np.append(polygon, [polygon[0]], axis=0)

        triangles, frames = ear_clipping(polygon)

        plot_polygon(polygon,triangles, frames)
    