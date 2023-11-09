-- Find the crime scene description
SELECT description
FROM crime_scene_reports
WHERE month = 7
    AND day = 28
    AND year = 2021
    AND street = 'Humphrey Street';

-- List interviews related to the theft
SELECT i.name, i.transcript
FROM interviews i
WHERE month = 7
    AND day = 28
    AND year = 2021
    AND i.transcript LIKE '%thief%'
ORDER BY i.name;

-- List people who made ATM withdrawals on a specific date and location
SELECT p.name
FROM people p
WHERE p.id IN (
        SELECT ba.person_id
        FROM atm_transactions at
            JOIN bank_accounts ba ON ba.account_number = at.account_number
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
    )
ORDER BY p.name;

-- List people who made phone calls on a specific date with a call duration less than 60 seconds
SELECT p.name
FROM people p
WHERE p.phone_number IN (
        SELECT pc.caller
        FROM phone_calls pc
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND duration <= 60
    )
ORDER BY p.name;

-- List people with a specific license plate activity on a specific date and time
SELECT p.name
FROM people p
WHERE p.license_plate IN (
        SELECT bsl.license_plate
        FROM bakery_security_logs bsl
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
            AND activity = 'exit'
    )
ORDER BY p.name;

-- Find the first flight from a specific city on a specific date
SELECT f.id, f.hour, f.minute, org.city, dst.city
FROM flights f
    JOIN airports org ON org.id = f.origin_airport_id
    JOIN airports dst ON dst.id = f.destination_airport_id
WHERE f.month = 7
    AND f.day = 29
    AND f.year = 2021
    AND org.city = 'Fiftyville'
ORDER BY f.hour, f.minute
LIMIT 1;

-- List people who were passengers on the first flight from a specific city on a specific date
SELECT p.name
FROM people p
WHERE p.passport_number IN (
        SELECT ps.passport_number
        FROM passengers ps
        WHERE ps.flight_id IN (
                SELECT f.id
                FROM flights f
                    JOIN airports org ON org.id = f.origin_airport_id
                WHERE f.month = 7
                    AND f.day = 29
                    AND f.year = 2021
                    AND org.city = 'Fiftyville'
                ORDER BY f.hour, f.minute
                LIMIT 1
            )
    )
ORDER BY p.name;

-- List people who meet multiple criteria (ATM withdrawal, phone call, license plate activity, and flight)
SELECT p.name
FROM people p
WHERE p.id IN (
        SELECT ba.person_id
        FROM atm_transactions at
            JOIN bank_accounts ba ON ba.account_number = at.account_number
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
    )
    AND p.phone_number IN (
        SELECT pc.caller
        FROM phone_calls pc
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND duration <= 60
    )
    AND p.license_plate IN (
        SELECT bsl.license_plate
        FROM bakery_security_logs bsl
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
            AND activity = 'exit'
    )
    AND p.passport_number IN (
        SELECT ps.passport_number
        FROM passengers ps
        WHERE ps.flight_id IN (
                SELECT f.id
                FROM flights f
                    JOIN airports org ON org.id = f.origin_airport_id
                WHERE f.month = 7
                    AND f.day = 29
                    AND f.year = 2021
                    AND org.city = 'Fiftyville'
                ORDER BY f.hour, f.minute
                LIMIT 1
            )
    )
ORDER BY p.name;

-- List people who received phone calls from a specific caller with a call duration less than 60 seconds
SELECT p.name
FROM people p
WHERE p.phone_number IN (
        SELECT pc.receiver
        FROM phone_calls pc
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND caller = (
                SELECT p.phone_number
                FROM people p
                WHERE p.name = 'Bruce'
            )
            AND duration <= 60
    )
ORDER BY p.name;
