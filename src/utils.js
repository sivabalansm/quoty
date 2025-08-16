export function convertToHash(string) {
  return CryptoJS.MD5(string).toString()
}
