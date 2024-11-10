import ctypes

from config.utils import get_lib_path


class Kuznechik:
    BLOCK_SIZE = 16 # Block size: 16 bytes (128 bits)
    KEY_SIZE = 32 # Key size: 32 bytes (256 bits)

    def __init__(self, lib_path: str):

        self.lib_kuznechik = ctypes.CDLL(lib_path)

    def encrypt(self, blk: bytes, key: bytes) -> bytes:

        out_blk = bytes(self.BLOCK_SIZE)

        self.lib_kuznechik.GOST_Kuz_Encrypt(blk, key, out_blk)

        return out_blk

    def decrypt(self, blk: bytes, key: bytes) -> bytes:

        out_blk = bytes(self.BLOCK_SIZE)

        self.lib_kuznechik.GOST_Kuz_Decrypt(blk, key, out_blk)

        return out_blk

kuznechik = Kuznechik(get_lib_path("kuznechik.so"))