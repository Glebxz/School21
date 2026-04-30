--DROP TABLE IF EXISTS users, games;

CREATE TABLE IF NOT EXISTS users (
    uuid UUID PRIMARY KEY,
    login TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS games (
    game_uuid UUID PRIMARY KEY,
    board JSON NOT NULL,

    is_ai BOOLEAN NOT NULL,

    player_x UUID REFERENCES users(uuid),
    player_o UUID,

    current_turn INT NOT NULL,
    current_state INT NOT NULL,
    winner UUID,
    start_time TIMESTAMPTZ
);