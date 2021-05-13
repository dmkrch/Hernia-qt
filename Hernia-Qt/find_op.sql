SELECT
	op_id,
	op_date,
	surg_name,
	op_title,
	pat_gender,
	pat_age,
	seq_type,
	seq_title,
	diagn_title,
	op_rec_days
FROM operations
INNER JOIN surgeons on surgeons.surg_id=operations.surg_id
WHERE 	(op_date BETWEEN "" AND "") AND
		(pat_age BETWEEN "" AND "") AND
		(op_rec_days BETWEEN "" AND "")
-- WHERE operations.seq_type IS NOT NULL AND
-- 	(seq_title ="кровотечение" OR  seq_title="пологого органа" OR seq_title="конверсия в открытую")
-- 