def paint_canvas(canvas, mask, color):

    assert canvas.ndim == 3
    assert canvas.shape[0] == mask.shape[0]
    assert canvas.shape[1] == mask.shape[1]
    assert len(color) == 3
    assert mask.dtype == bool

    canvas[..., 0][mask] = color[0]
    canvas[..., 1][mask] = color[1]
    canvas[..., 2][mask] = color[2]

    return canvas
