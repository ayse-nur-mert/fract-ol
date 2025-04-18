### Fract-ol: Fractal Renderer
## What are Fractals?
Fractals are geometric shapes that are mathematically defined and exhibit self-replicating structures. These shapes repeat similar patterns at various scales, which is why they are known for their self-similarity. In other words, when you examine a part of a fractal, you can observe a pattern that resembles the entire structure.

Key Features of Fractals
Self-Similarity: Fractals are characterized by the repetition of a pattern at different scales. For example, when you zoom in on a part of a fractal, that part may resemble the whole fractal.

Complexity at Large Scales: Fractals can be mathematically complex, but they can often be modeled by simple mathematical formulas.

Fractal Dimension: Fractals often have fractional dimensions instead of whole numbers, setting them apart from traditional geometric shapes. This feature is known as fractal dimension.

Infinite Detail: Fractals often contain infinite detail. The closer you zoom into a fractal, the more details you uncover. For example, the Mandelbrot set reveals new patterns every time you zoom in further.
## Introduction

Fract-ol is a C-based project that allows you to explore two well-known fractals: **Mandelbrot** and **Julia**. With interactive controls, you can zoom in/out and modify the fractal's appearance by adjusting the number of iterations.

This project was developed as part of a programming challenge to explore fractals and their mathematical beauty.

## Features

- **Mandelbrot Set Rendering**  
  Visualize the famous Mandelbrot set. A complex and fascinating set of points in the complex plane.

- **Julia Set Rendering**  
  Explore the Julia set, which is closely related to the Mandelbrot set, but each point in the set corresponds to a different Julia fractal.

- **Interactive Controls**  
  - **Zooming**: Use the **scroll wheel** of your mouse to zoom in and out on the fractal.
  - **Iteration Control**: Press the **'E'** and **'Q'** keys to decrease or increase the number of iterations. This will change the detail of the fractal. A higher iteration count gives a more detailed fractal but requires more computation.
  
## Requirements

To build and run this project, you will need the following:

- **minilibx** library for graphics rendering.  
  Install it via [Minilibx documentation](https://github.com/42Paris/minilibx).

## Installation

### Clone the Repository

```bash
git clone https://github.com/ayse-nur-mert/fract-ol.git
cd fract-ol
```

### Build the Project

Ensure you have **minilibx** installed. Once it's set up, run the following commands to compile the project:

```bash
make
```

### Run the Application

Once the project is compiled, run it with:

```bash
./fractol
```

You can specify the fractal type (Mandelbrot or Julia) when running the program:

```bash
./fractol mandelbrot
```

or

```bash
./fractol julia
```

## Controls

- **Zooming**: Scroll the mouse wheel to zoom in and out of the fractal.
- **Iteration Control**: Press the **'E'** key to decrease the number of iterations and **'Q'** to increase the number of iterations.
- **Quit**: Press **'ESC'** to close the application.

## Understanding the Fractals

### Mandelbrot Set

The Mandelbrot set is a set of complex numbers that is defined by iterating the equation:

\[
z_{n+1} = z_n^2 + c
\]

Where \( z_n \) is a complex number and \( c \) is a constant complex number. The Mandelbrot set is the set of all complex numbers \( c \) for which the sequence does not tend to infinity when iterated. The boundary of the Mandelbrot set is a fractal, which has intricate and infinite detail the more you zoom in.

### Julia Set

The Julia set is similar to the Mandelbrot set, but instead of iterating over a set of values of \( c \), you use a fixed value for \( c \) and iterate over every point in the complex plane. The resulting fractal pattern will change depending on the chosen value for \( c \). This makes the Julia set appear like a "family" of fractals, where the shape can change dramatically based on the initial condition.

## Screenshots

Here are some examples of the rendered fractals:

### Mandelbrot Set Example

![Mandelbrot Set](https://upload.wikimedia.org/wikipedia/commons/a/a8/Mandelbrot_set_and_boundary.png)

### Julia Set Example

![Julia Set](https://upload.wikimedia.org/wikipedia/commons/4/42/Julia_set_%28complex_dynamics%29.png)
