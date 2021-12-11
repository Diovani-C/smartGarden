/** @type {import('ts-jest/dist/types').InitialOptionsTsJest} */
module.exports = {
  testPathIgnorePatterns: ['/node_modules/', '/dist/', '/public/'],
  modulePathIgnorePatterns: ['/public/', '/dist/', '/node_modules/'],
  preset: 'ts-jest',
  testEnvironment: 'node',
};
