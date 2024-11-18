import ctypes

from config.utils import get_lib_path


class Kuznechik:
    BLOCK_SIZE = 16 # Block size: 16 bytes (128 bits)
    KEY_SIZE = 32 # Key size: 32 bytes (256 bits)

    def __init__(self, lib_path: str):
        """
        Loads the Kuznechik encryption shared library (GOST R 34.12-2015) from the specified path.

        Parameters:
            lib_path (str): Path to the precompiled C++ shared library containing the Kuznechik encryption and decryption functions (`GOST_Kuz_Encrypt` and `GOST_Kuz_Decrypt`).

        Note:
            The shared library must be precompiled from the following C++ source files: `kuznechik.cpp`, `kuznechik.h` and `kuznechik_const.h`.
            The shared library includes additional internal functions that are not exposed to Python.
        """

        self.lib_kuznechik = ctypes.CDLL(lib_path)

    def encrypt(self, blk: bytes, key: bytes) -> bytes:
        """
        Encrypts a 16-byte block of data using the Kuznechik (GOST R 34.12-2015) block cipher.

        Parameters:
            blk (bytes): 16-byte block of data to encrypt.
            key (bytes): 32-byte encryption key.

        Returns:
            bytes: 16-byte encrypted block.

        Note:
            If the block of data or key is shorter than required, zero padding is added to the left side.
        """

        out_blk = bytes(self.BLOCK_SIZE)
        blk = self.zero_padding(blk, self.BLOCK_SIZE)
        key = self.zero_padding(key, self.KEY_SIZE)

        self.lib_kuznechik.GOST_Kuz_Encrypt(blk, key, out_blk)

        return out_blk

    def decrypt(self, blk: bytes, key: bytes) -> bytes:
        """
        Decrypts a 16-byte encrypted block using the Kuznechik (GOST R 34.12-2015) block cipher.

        Parameters:
            blk (bytes): 16-byte encrypted block.
            key (bytes): 32-byte decryption key.

        Returns:
            bytes: Decrypted block of data with zero padding removed.

        Note:
            If the key is shorter than required, zero padding is added to the left side.
            After decryption, zero padding is removed from the left side of the decrypted block.
        """

        out_blk = bytes(self.BLOCK_SIZE)
        key = self.zero_padding(key, self.KEY_SIZE)

        self.lib_kuznechik.GOST_Kuz_Decrypt(blk, key, out_blk)

        out_blk = self.remove_zero_padding(out_blk)

        return out_blk

    @staticmethod
    def zero_padding(input_bytes: bytes, target_size: int) -> bytes:
        """
        Adds zero padding to the byte string to match the specified size.

        Parameters:
            input_bytes (bytes): The byte string to be padded.
            target_size (int): The target size of the byte string.

        Returns:
            bytes: The padded byte string, or the original byte string if its size already matches the target size.

        Note:
            The padding is added to the left side of the byte string if its size is less than the target size.
            If the size of the byte string already matches the target size, no padding is added.
        """

        return input_bytes.rjust(target_size, b'\x00')

    @staticmethod
    def remove_zero_padding(padded_bytes: bytes) -> bytes:
        """
        Removes zero padding from the byte string.

        Parameters:
            padded_bytes (bytes): The byte string with padding to be removed.
                If no padding is present, the original byte string is returned unchanged.

        Returns:
            bytes: The byte string with zero padding removed.

        Note:
            The padding is removed from the left side of the byte string.
        """

        return padded_bytes.lstrip(b'\x00')

kuznechik = Kuznechik(get_lib_path("kuznechik.so"))