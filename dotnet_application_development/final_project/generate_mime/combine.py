import os

combined = open('combined.csv', 'w')
for i in os.listdir('./'):
    if i.endswith('.csv'):
        with open(i, 'r') as f:
            for line in f.readlines()[1:]:
                combined.write(line)
combined.close()