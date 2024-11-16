from typing import Annotated

from fastapi import APIRouter, Query, HTTPException


tools_router = APIRouter(prefix="/tools", tags=["tools"])

@tools_router.get("/str-to-hex", status_code=200)
async def str_to_hex(data_str: Annotated[str, Query(max_length=25)]) -> dict[str, str]:
    """
    Converts a regular string to a hex string.

    This endpoint takes a regular UTF-8 string as input and converts it to its hexadecimal representation.

    Parameters:
    - **data_str**: The regular string to be converted.
      - Must be a valid UTF-8 string.
      - Length must not exceed 25 characters.

    Returns:
    - A JSON object with the key `data_hex`, containing the hexadecimal representation of the input string.

    Example:
    ```
    Input: "Hello"
    Output: {"data_hex": "48656c6c6f"}
    ```
    """

    data_hex = data_str.encode("utf-8").hex()

    return {"data_hex": data_hex}

@tools_router.get("/hex-to-str", status_code=200)
async def hex_to_str(data_hex: Annotated[str, Query(max_length=100, pattern="^[0-9a-fA-F]+$")]) -> dict[str, str]:
    """
    Converts a hex string to a regular string.

    This endpoint takes a hexadecimal string as input and converts it to a regular UTF-8 string.

    Parameters:
    - **data_hex**: The hexadecimal string to be converted.
      - Must contain only valid hexadecimal characters `[0-9a-fA-F]`.
      - Length must be even and not exceed 100 characters.

    Returns:
    - A JSON object with the key `data_str`, containing the decoded string.

    Raises:
    - **400 Bad Request**: 
        - If the hex string does not have an even number of characters.
        - If the hex string cannot be decoded into valid UTF-8 encoded text.

    Example:
    ```
    Input: "48656c6c6f"
    Output: {"data_str": "Hello"}
    ```
    """

    if len(data_hex) % 2 != 0:
        raise HTTPException(status_code=400, detail="Hex string must have an even number of characters.")

    try:
        data_str = bytes.fromhex(data_hex).decode("utf-8")

    except UnicodeDecodeError:
        raise HTTPException(status_code=400, detail="The input hex string could not be decoded into valid UTF-8 encoded text.")

    return {"data_str": data_str}

@tools_router.get("/hex-info", status_code=200)
async def hex_info(data_hex: Annotated[str, Query(max_length=100, pattern="^[0-9a-fA-F]+$")]) -> dict[str, int]:
    """
    Provides information about a hex string.

    This endpoint takes a hexadecimal string as input and returns information about its length in different units.

    Parameters:
    - **data_hex**: The hexadecimal string for which information is requested.
      - Must contain only valid hexadecimal characters `[0-9a-fA-F]`.
      - Length must be even and not exceed 100 characters.

    Returns:
    - A JSON object with the following keys:
      - **len_hex**: The length of the hex string (number of characters).
      - **len_byte**: The length of the hex string in bytes (number of characters / 2).
      - **len_bit**: The length of the hex string in bits (number of characters * 4).

    Raises:
    - **400 Bad Request**: 
        - If the hex string does not have an even number of characters.

    Example:
    ```
    Input: "48656c6c6f"
    Output: {"len_hex": 10, "len_byte": 5, "len_bit": 40}
    ```
    """

    if len(data_hex) % 2 != 0:
        raise HTTPException(status_code=400, detail="Hex string must have an even number of characters.")

    return {"len_hex": len(data_hex), "len_byte": len(data_hex) * 0.5, "len_bit": len(data_hex) * 4}