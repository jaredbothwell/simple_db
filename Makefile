db: src/db.c
	gcc src/db.c -o bin/db

run: db
	./bin/db mydb.db

clean:
	rm -f bin/db bin/*.db

test: db
	bundle exec rspec

format: *.c
	clang-format -style=file:.clang_format -i *.c