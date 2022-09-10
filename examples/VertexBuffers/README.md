# VertexBuffers example

Shows 3 different ways of how layout and configure vertex buffers in GPU memory:

a) Diamond, uses separate buffers for each attribute
```
Buffer 0: |x|y|z|x|y|z|...
Buffer 1: |r|g|b|r|g|b|...

Buffer 0 -> Binding 0 -> Location 0: Position
Buffer 1 -> Binding 1 -> Location 1: Color 
```

b) Square, has all attributes in one buffer, *deinterleaved*
```
Buffer 0: |x|y|z|x|y|z|...|r|g|b|r|g|b|...
                          ^ offset for the 2. binding

Buffer 0 -> Binding 0 -> Location 0: Position
         -> Binding 1 -> Location 1: Color
```

c) Triangle, has all attributes in one buffer, *interleaved*
```
          | Vertex 0    | Vertex 1    |
           ------------- -------------  ...
Buffer 0:  |x|y|z|r|g|b| |x|y|z|r|g|b|
                         ^ relative offset

Buffer 0 -> Binding 0 -> Location 0: Position
                      -> Location 1: Color
```
- also uses custom vertex type, with unsigned 8 bit integer as color, that
needs to be normalized