-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene report:
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2021 AND street = 'Humphrey Street';
-- Crime took place at 10:15am at the bakery, 3 witnesses were interviewed.

-- Check interview transcripts and names of witnesses:
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28 AND year = 2021 AND transcript LIKE '%bakery%';

-- Ruth: The thief's car could be in security footage from the bakery parking lot, within then minutes after theft.
-- Check bakery security logs license plates:
SELECT license_plate FROM bakery_security_logs
WHERE  month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit';
-- Check information of people owning these license plates:
SELECT * FROM people WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit'
);
-- Check who of these people made phonecalls between 10:15am and 10:25am:
SELECT caller, name as caller_name, receiver, passport_number, license_plate FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND caller IN (
    SELECT phone_number FROM people WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit' AND duration < 60
    )
);
-- Check who received these phonecalls
SELECT caller, receiver, name as receiver_name, passport_number, license_plate FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60 AND caller IN (
    SELECT phone_number FROM people WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit'
    )
);

-- Combine caller and receiver data in a single table
SELECT caller, people1.name as caller_name, people1.passport_number AS caller_passport, people1.license_plate AS caller_license_plate, receiver, people2.name as receiver_name, people2.passport_number AS receiver_passport, people2.license_plate AS receiver_license_plate FROM phone_calls
JOIN people people1 ON phone_calls.caller = people1.phone_number
JOIN people people2 ON phone_calls.receiver = people2.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60 AND caller IN (
    SELECT phone_number FROM people WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit'
    )
);


-- Eugene: Seen the thief before 10:15am, widrawing money at the ATM on Leggett Street.
-- Check who made transactions at that atm on that day
SELECT name FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Raymond: When leaving, the thief called someone saying that they'd take the first flight out of Fiftyville the next morning and asked for the other person to buy the ticket.
-- Check which of the people that made phonecalls shorter than a minute on the specified moment with a license plate seen at the backery was also at the atm that day
SELECT caller, people1.name as caller_name, people1.passport_number AS caller_passport, people1.license_plate AS caller_license_plate, receiver, people2.name as receiver_name, people2.passport_number AS receiver_passport, people2.license_plate AS receiver_license_plate FROM phone_calls
JOIN people people1 ON phone_calls.caller = people1.phone_number
JOIN people people2 ON phone_calls.receiver = people2.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60 AND caller IN (
    SELECT phone_number FROM people WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit'
    )
)
AND caller_name IN (
    SELECT name FROM atm_transactions
    JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
    JOIN people ON bank_accounts.person_id = people.id
    WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
);

-- Check which airports
SELECT * FROM airports;

-- Check first flight on 07-29-2021 leaving from Fiftyville
SELECT * FROM flights WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour LIMIT 1;

-- Check destination of thief
SELECT city AS destination FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id = (
    SELECT id FROM airports WHERE city = 'Fiftyville'
) ORDER BY hour LIMIT 1;

-- Check which of the suspects was on this flight
SELECT passport_number FROM passengers WHERE flight_id = (
    SELECT flights.id as id FROM flights
    JOIN airports ON flights.destination_airport_id = airports.id
    WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id = (
    SELECT id FROM airports WHERE city = 'Fiftyville'
    ) ORDER BY hour LIMIT 1
);

-- Identify the thief
SELECT DISTINCT people1.name as thief FROM phone_calls
JOIN people people1 ON phone_calls.caller = people1.phone_number
JOIN people people2 ON phone_calls.receiver = people2.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60 AND caller IN (
    SELECT phone_number FROM people WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit'
    )
)
AND thief IN (
    SELECT name FROM atm_transactions
    JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
    JOIN people ON bank_accounts.person_id = people.id
    WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
)
AND people1.passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id = (
        SELECT flights.id as id FROM flights
        JOIN airports ON flights.destination_airport_id = airports.id
        WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
        )
        ORDER BY hour LIMIT 1
    )
);

-- Identify the accomplice
SELECT people2.name as accomplice FROM phone_calls
JOIN people people1 ON phone_calls.caller = people1.phone_number
JOIN people people2 ON phone_calls.receiver = people2.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60 AND caller IN (
    SELECT phone_number FROM people WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = 'exit'
    )
)
AND people1.name IN (
    SELECT name FROM atm_transactions
    JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
    JOIN people ON bank_accounts.person_id = people.id
    WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
)
AND people1.passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id = (
        SELECT flights.id as id FROM flights
        JOIN airports ON flights.destination_airport_id = airports.id
        WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
        )
        ORDER BY hour LIMIT 1
    )
);