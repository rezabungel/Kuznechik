from typing import Annotated

from fastapi import APIRouter, Query, HTTPException

from encryption.kuznechik import kuznechik


router = APIRouter(prefix="/kuznechik", tags=["kuznechik"])

@router.post("/encrypt", status_code=200)
async def encrypt(blk: Annotated[str, Query(max_length=32, pattern="^[0-9a-fA-F]+$")],
                  key: Annotated[str, Query(max_length=64, pattern="^[0-9a-fA-F]+$")]) -> str:
    """
    Encrypts a 16-byte block of data using the Kuznechik (GOST R 34.12-2015) block cipher.

    This endpoint encrypts a block of data (`blk`) using a provided encryption key (`key`).<br>
    Both the block and key are represented as hexadecimal strings.

    **Zero padding**:
    - If the block of data is less than 16 bytes, zero padding is added to the left side of the byte string to match 16 bytes.
    - If the encryption key is less than 32 bytes, zero padding is added to the left side of the byte string to match 32 bytes.
    - This ensures compliance with the Kuznechik cipher's requirements for fixed block of data and encryption key sizes.

    Parameters:
    - **blk**: The block of data to be encrypted, represented as a hexadecimal string.
      - Must be no more than 16 bytes (32 hex characters). Zero padding will be applied if shorter.
      - Must contain only valid hexadecimal characters `[0-9a-fA-F]`.
      - Length must be even.

    - **key**: The encryption key, represented as a hexadecimal string.
      - Must be no more than 32 bytes (64 hex characters). Zero padding will be applied if shorter.
      - Must contain only valid hexadecimal characters `[0-9a-fA-F]`.
      - Length must be even.

    Returns:
    - A hexadecimal string representing the encrypted block of exactly 16 bytes (32 hex characters).

    Raises:
    - **400 Bad Request**:
        - If the `blk` or `key` does not have an even number of characters.
    - **422 Unprocessable Entity**:
        - If the input parameters do not meet the validation requirements.

    Example:
    ```
    Input:
    blk: "48656c6c6f"
    key: "576f726c64"

    Output:
    "8479704f8d801853d314e7e060f67a80"

    Explanation:
    - Block of data is zero padded to "000000000000000000000048656c6c6f".
    - Encryption key is zero padded to "000000000000000000000000000000000000000000000000000000576f726c64".
    - Resulting encrypted block is returned as a hexadecimal string.
    ```
    """

    if len(blk) % 2 != 0:
        raise HTTPException(status_code=400, detail="The block of data to be encrypted must have an even number of characters.")

    if len(key) % 2 != 0:
        raise HTTPException(status_code=400, detail="The encryption key must have an even number of characters.")

    blk = bytes.fromhex(blk)
    key = bytes.fromhex(key) 

    out_blk = kuznechik.encrypt(blk, key)
    out_blk = out_blk.hex()

    return out_blk

@router.post("/decrypt", status_code=200)
async def decrypt(blk: Annotated[str, Query(min_length=32, max_length=32, pattern="^[0-9a-fA-F]+$")],
                  key: Annotated[str, Query(max_length=64, pattern="^[0-9a-fA-F]+$")]) -> str:
    """
    Decrypts a 16-byte encrypted block using the Kuznechik (GOST R 34.12-2015) block cipher.

    This endpoint decrypts an encrypted block (`blk`) using a provided decryption key (`key`).<br>
    Both the block and key are represented as hexadecimal strings.

    **Zero padding**:
    - The encrypted block is always exactly 16 bytes and does not require zero padding.
    - If the decryption key is less than 32 bytes, zero padding is added to the left side of the byte string to match 32 bytes.
    - This ensures compliance with the Kuznechik cipher's requirements for fixed encrypted block and decryption key sizes.
    - After decryption, zero padding is removed from the left side of the decrypted block.

    Parameters:
    - **blk**: The encrypted block to be decrypted, represented as a hexadecimal string.
      - Must be exactly 16 bytes (32 hex characters).
      - Must contain only valid hexadecimal characters `[0-9a-fA-F]`.

    - **key**: The decryption key, represented as a hexadecimal string.
      - Must be no more than 32 bytes (64 hex characters). Zero padding will be applied if shorter.
      - Must contain only valid hexadecimal characters `[0-9a-fA-F]`.
      - Length must be even.

    Returns:
    - A hexadecimal string representing the decrypted block. Zero padding is removed from the left side of the decrypted block.

    Raises:
    - **400 Bad Request**: 
        - If the `key` does not have an even number of characters.
    - **422 Unprocessable Entity**:
        - If the input parameters do not meet the validation requirements.

    Example:
    ```
    Input:
    blk: "8479704f8d801853d314e7e060f67a80"
    key: "576f726c64"

    Output:
    "48656c6c6f"

    Explanation:
    - The input encrypted block is "8479704f8d801853d314e7e060f67a80".
    - Decryption key is zero padded to "000000000000000000000000000000000000000000000000000000576f726c64".
    - After decryption, the decrypted block contains zero padding: "000000000000000000000048656c6c6f"
    - Zero padding is removed from the left side of the decrypted block, resulting in the hexadecimal string "48656c6c6f"
    ```
    """

    if len(key) % 2 != 0:
        raise HTTPException(status_code=400, detail="The decryption key must have an even number of characters.")

    blk = bytes.fromhex(blk)
    key = bytes.fromhex(key)

    out_blk = kuznechik.decrypt(blk, key)
    out_blk = out_blk.hex()

    return out_blk
