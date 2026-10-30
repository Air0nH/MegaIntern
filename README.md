# MegaIntern

MegaIntern was an experimental, pocket-sized USB keyboard-macro controller developed in November 2021. It was inspired by earlier Chromebook enrollment automation work, but is a **separate project** from the original working Intern enrollment devices.

The concept combined a binary program selector, a small OLED display, and a play button so that one device could offer multiple keyboard routines. I built an unfinished physical prototype on **perfboard**.

## Hardware concept

The archived [`main.ino`](main.ino) targets an Arduino capable of USB HID keyboard emulation and uses a 128 × 32 SSD1306 OLED over I²C. I recall using the same Arduino board model for MegaIntern, the original Intern devices, and ButtonBox, but the exact model is no longer known.

| Input or display control | Arduino pin |
|---|---:|
| Play button | 5 |
| Selector bit 1 | 6 |
| Selector bit 2 | 7 |
| Selector bit 4 | 8 |
| Selector bit 8 | 9 |
| OLED reset definition | 4 |

The OLED is configured at I²C address `0x3C` in the source. The four selector bits represent as many as sixteen program positions.

## What was implemented

The surviving firmware defines sixteen switch cases, but **only four contain macro actions**. The others are placeholders. Its display functions include progress graphics. This was a working-but-incomplete prototype, not a completed sixteen-program appliance.

There is no verified stop-button routine in the surviving firmware; I do not remember whether a physical stop control was fitted to the perfboard prototype. The exact final flashed sketch and real-world behavior of every program have not been reconstructed.

## Source and historical context

The project's keyboard automation ideas grew out of work with earlier dedicated Chromebook enrollment tools, which used an Amplified IT Centipede-derived sketch. That third-party enrollment software should not be confused with MegaIntern's source or attributed to this project.

This repository is an archival snapshot, not a maintained device or a verified flashing/wiring guide. Review any macro payloads before reusing them; USB HID automation can send unexpected keystrokes to the connected computer.

## License status

No repository-level `LICENSE` file was present when this documentation was prepared. No license is implied by this README; an explicit licensing decision should precede redistribution of newly contributed code or third-party material.
