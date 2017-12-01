CREATE TABLE IF NOT EXISTS data (
	id integer PRIMARY KEY,
	comparator_id integer NOT NULL,
	is_compare_target_sequence integer NOT NULL,
	compare_sequence_id integer NOT NULL,
	actual_sequence_id integer NOT NULL,
	similarity REAL NOT NULL
);