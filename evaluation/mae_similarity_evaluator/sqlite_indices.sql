CREATE INDEX `cid-tid-sid` ON `data` (
	`comparator_id`,
	`compare_sequence_id`,
	`actual_sequence_id`
);

CREATE INDEX `path` ON `sequences` (
	`path`
);

CREATE INDEX `name` ON `comparators` (
	`name`
);