import { parseCSV, fillTheLastXValue, filterDatasetsByDate } from '../src/lib/utilities';

const csvInput = '1,55.0,2,59.9,3,34.5,1312462345\n2,56.9,1312462450\n1,57.0,1312482346';

const ParsedCSV = [
	{
		ID: 1,
		data: [
			{ x: 1312462345 * 1000, y: 55.0 },
			{ x: 1312482346 * 1000, y: 57.0 }
		]
	},
	{
		ID: 2,
		data: [
			{ x: 1312462345 * 1000, y: 59.9 },
			{ x: 1312462450 * 1000, y: 56.9 }
		]
	},
	{
		ID: 3,
		data: [{ x: 1312462345 * 1000, y: 34.5 }]
	}
];

const ParsedAndFilled = [
	{
		ID: 1,
		data: [
			{ x: 1312462345 * 1000, y: 55.0 },
			{ x: 1312482346 * 1000, y: 57.0 }
		]
	},
	{
		ID: 2,
		data: [
			{ x: 1312462345 * 1000, y: 59.9 },
			{ x: 1312462450 * 1000, y: 56.9 },
			{ x: 1312482346 * 1000, y: 56.9 }
		]
	},
	{
		ID: 3,
		data: [
			{ x: 1312462345 * 1000, y: 34.5 },
			{ x: 1312482346 * 1000, y: 34.5 }
		]
	}
];

test('Parse string csv file to array of sensor data', () => {
	expect(parseCSV(csvInput)).toStrictEqual(ParsedCSV);
});

test('Fill the last value', () => {
	expect(fillTheLastXValue(ParsedCSV)).toStrictEqual(ParsedAndFilled);
});

test('Filter the datasets by date', () => {});
