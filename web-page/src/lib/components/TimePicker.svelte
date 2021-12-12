<script lang="ts">
	import State from '$lib/state';
	import { minimum2IntegerDigits } from '$lib/utilities';

	export let minDate: number;
	export let maxDate: number;
	let from = '';
	let to = '';

	$: min = valueToDateInput(minDate);
	$: max = valueToDateInput(maxDate);

	const week = 60 * 60 * 24 * 7 * 1000;

	$: {
		if (maxDate - week >= minDate) {
			from = valueToDateInput(maxDate - week);
		} else {
			from = min;
		}
		to = max;
	}

	$: State.updateFrom(from);
	$: State.updateTo(to);

	function valueToDateInput(localValue: number): string {
		const localDate = new Date(localValue);
		return `${localDate.getFullYear()}-${minimum2IntegerDigits(
			localDate.getMonth() + 1
		)}-${minimum2IntegerDigits(localDate.getDate())}`;
	}
</script>

<div class="time-picker-grid">
	<div class="from">
		<label for="from">De:</label>
		<input type="date" id="from" bind:value={from} {min} {max} />
	</div>
	<div class="to">
		<label for="to">Até:</label>
		<input type="date" id="to" bind:value={to} {min} {max} />
	</div>
</div>

<style>
	.time-picker-grid {
		display: grid;
		justify-items: start;
		align-items: center;
		gap: 4px;
		grid-template-columns: 1fr 1fr;
		grid-template-rows: 32px;
	}

	.from {
		justify-self: end;
	}

	input {
		color: black;
	}

	label {
		justify-self: end;
	}
</style>
