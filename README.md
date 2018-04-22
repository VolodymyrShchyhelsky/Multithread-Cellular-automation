# Multithread-Cellular-automation

Rules: All objects on the field have identic reproduction rules. Initially all objects are randomly divided by N(1..10) diferent species. Each species has its own color on the field. Only one individual can ocuppy a single unit of space. Each individual can reproduce itself in asexual, bisexual or "three sexual" way once per a unit of time. An asexual individual creates children who spread out randomly in the assigned radius (if a unit of space is free, a child occupies it; if not, a child either occupies this unit or dies with equal chance). A bisexual ("three sexual") individual must find one (two) partner(s) in the assigned radius to multiply. After multiplication an individual dies.

Parameters:
SexBreed: asexual, bisexual or three sexual"/n"
Size: height and width of the field
Resettlement radius and Partner Find Radius: maximal distanse(in height or width) from point
Fertility: count of children
Count of kind: 1-10
Density: count of individual in one kinds
Time: number of generations
