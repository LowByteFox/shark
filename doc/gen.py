# SPDX-License-Identifier: Apache-2.0
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import json


def plot_bits(fields, out, total_bits=32):
    fig, ax = plt.subplots(figsize=(12, 1.25))

    ax.set_xlim(-1, total_bits + 1)
    ax.set_ylim(0, 2)
    ax.axis('off')
    
    for start, end, name in fields:
        width = end - start + 1
        rect = patches.Rectangle(
            (start, 0.5), 
            width, 
            1, 
            facecolor='white', 
            edgecolor='black', 
            linewidth=1.5
        )
        ax.add_patch(rect)
        
        ax.text(
            start + width / 2, 
            1, 
            name, 
            ha='center', 
            va='center', 
            color='black', 
            fontsize=12,
            fontfamily="monospace",
            fontweight="bold"
        )
        
        ax.text(start, 0.3, str(32 - start), ha='center', va='top', fontsize=11)

    start, end, name = fields[0]
    ax.text(end + 1, 0.3, str(31 - end), ha='center', va='top', fontsize=11)

    plt.savefig(out, bbox_inches='tight')


def transform(arr):
    out = []

    end = 32

    for length, name in arr:
        range_start = 32 - end
        range_end = range_start + length - 1
        out.append((range_start, range_end, name))

        end -= length
    out.reverse()

    return out


with open("data.json") as f:
    instructions = json.load(f)

for key in instructions:
    plot_bits(transform(instructions[key]), f"pdfs/{key}.pdf")

with open("pdfs/done", "w") as f:
    pass