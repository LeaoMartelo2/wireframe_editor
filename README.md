Level editor for [wireframe_game](https://github.com/LeaoMartelo2/wireframe_game)

# File Format Specification:

- The editor produces a `.wireframe` file, that gets fed in the engine to be displayed on the screen.

- The format is split in 3 different sections, `Ground`, `Geometry (solids)` and `Props`;

## Geometry (solids)

- This section is ment to define solid walls and map geometry in general.
- This is also the first section of the `.wireframe` format.
```

1 //amount of elements in the map
#0 //marking the start of the first solid
10  // element x of size (float)
20  // element y of size (float)
30  // element z of size (float)
100 // element x of pos  (float)
200 // element y of pos  (float)
300 // element z of pos  (float)
0 //see_through boolean  (bool)

```
