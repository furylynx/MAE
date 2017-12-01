CREATE TABLE IF NOT EXISTS sequences (
	id integer PRIMARY KEY,
	path text NOT NULL UNIQUE,
	filename text NOT NULL,
	directory text NOT NULL,
	name text NOT NULL,
	score blob NOT NULL,
	defined integer not null
);