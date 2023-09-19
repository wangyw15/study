import sqlite3
import sys
import time
from pathlib import Path
from tqdm import tqdm

db_path = Path('test.db')
count = 10**7
target = 'test114514'

if len(sys.argv) > 1:
    if sys.argv[1].lower() == 'generate':
        # delete existing db
        if db_path.exists():
            db_path.unlink()

        # generate
        db = sqlite3.connect(db_path)
        c = db.cursor()

        # without index
        c.execute('create table if not exists test_noindex (id integer, data text)')
        for i in tqdm(range(count), desc='without index'):
            c.execute(f"insert into test_noindex values ({i}, 'test{i}')")
        
        # with index
        c.execute('create table if not exists test_index (id integer, data text)')
        for i in tqdm(range(count), desc='with index'):
            c.execute(f"insert into test_index values ({i}, 'test{i}')")
        
        print('creating index...')
        c.execute('create index if not exists index_data on test_index (data)')
        db.commit()
        db.close()
        
    elif sys.argv[1].lower() == 'test':
        if not db_path.exists():
            print('db not found, please generate first')
        else:
            print('testing...')
            db = sqlite3.connect(db_path)
            c = db.cursor()

            # test without index
            start = time.perf_counter()
            c.execute('select * from test_noindex where data == "{target}"')
            print('unindexed time:', (time.perf_counter() - start)*1000)

            # test with index
            start = time.perf_counter()
            c.execute('select * from test_index where data == "{target}"')
            print('  indexed time:', (time.perf_counter() - start)*1000)
