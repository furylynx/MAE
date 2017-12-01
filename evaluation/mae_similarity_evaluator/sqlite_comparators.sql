CREATE TABLE IF NOT EXISTS comparators (
	id integer PRIMARY KEY,
	name text NOT NULL UNIQUE,
	description text NOT NULL
);